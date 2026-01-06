#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <queue>
#include <thread>
#include <mutex>
#include "network/GameServer.hpp"
#include <Network/PacketSerializer.hpp>

namespace te {
namespace network {

GameServer::GameServer(uint16_t port,
    const std::string& protocol)
    : Server(protocol, port, net::ProtocolManager()),
    _protocol_type(protocol == "TCP" ?
    net::SocketType::TCP : net::SocketType::UDP)
    , _port(port)
    , _running(false) {
}

GameServer::~GameServer() {
    if (_running) {
        stopGameServer();
    }
}

bool GameServer::startGameServer() {
    if (!start()) {
        std::cerr << "[GameServer] Failed to start server" << std::endl;
        return false;
    }

    // Set non-blocking mode for UDP/TCP
    setNonBlocking(true);

    _running = true;
    std::cout << "[GameServer] Server started on port " << _port << std::endl;

    startNetworkThread();
    return true;
}

void GameServer::stopGameServer() {
    stopNetworkThread();

    stop();
    _running = false;
    _clients.clear();
    std::cout << "[GameServer] Server stopped" << std::endl;
}

void GameServer::update(float delta_time) {
    if (!_running)
        return;

    std::queue<IncomingPacket> packets_to_process;
    {
        std::lock_guard<std::mutex> lock(_incoming_mutex);
        packets_to_process.swap(_incoming_packets);
    }

    while (!packets_to_process.empty()) {
        IncomingPacket& packet = packets_to_process.front();

        if (!packet.data.empty()) {
            uint8_t packet_code = packet.data[0];
            std::vector<uint8_t> payload(packet.data.begin() + 1,
                packet.data.end());

            auto handler_it = _on_packet_received_map.find(packet_code);
            if (handler_it != _on_packet_received_map.end()) {
                handler_it->second(payload, packet.sender);
            } else {
                std::cerr << "[GameServer] No handler registered for "
                          << "packet code: "
                          << static_cast<int>(packet_code) << " from "
                          << packet.sender.getIP() << ":"
                          << packet.sender.getPort() << std::endl;
            }
        }
        packets_to_process.pop();
    }
}

bool GameServer::sendTo(const net::Address& client,
    const std::vector<uint8_t>& data) {
    if (!_running || data.empty())
        return false;

    try {
        if (_protocol_type == net::SocketType::UDP) {
            udpSend(client, data);
        } else {
            auto it = _address_to_fd.find(client);
            if (it != _address_to_fd.end()) {
                tcpSend(it->second, data);
            } else {
                return false;
            }
        }
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[GameServer] Failed to send to " << client.getIP()
                  << ":" << client.getPort() << " - " << e.what() << std::endl;
        return false;
    }
}

void GameServer::broadcastToAll(const std::vector<uint8_t>& data,
    const std::optional<net::Address>& exclude) {
    if (!_running || data.empty()) return;

    for (const auto& [addr, info] : _clients) {
        if (exclude.has_value() && addr == exclude.value())
            continue;
        sendTo(addr, data);
    }
}

void GameServer::receive(int timeout, int maxInputs) {
    if (!_running)
        return;

    try {
        if (_protocol_type == net::SocketType::UDP) {
            udpReceive(timeout, maxInputs);
        } else {
            tcpReceive(timeout);
        }
    } catch (const std::exception& e) {
        std::cerr << "[GameServer] Receive failed: " << e.what() << std::endl;
    }
}

void GameServer::registerPacketHandler(uint8_t key, PacketCallback callback) {
    _on_packet_received_map[key] = callback;
}

void GameServer::unregisterPacketHandler(uint8_t key) {
    _on_packet_received_map.erase(key);
}

void GameServer::setClientConnectCallback(ClientConnectCallback callback) {
    _on_client_connect = callback;
}

void GameServer::setClientDisconnectCallback(
    ClientDisconnectCallback callback) {
    _on_client_disconnect = callback;
}

bool GameServer::isRunning() const {
    return _running;
}

size_t GameServer::getClientCount() const {
    return _clients.size();
}

std::vector<net::Address> GameServer::getConnectedClients() const {
    std::vector<net::Address> clients;
    clients.reserve(_clients.size());
    for (const auto& [addr, info] : _clients) {
        clients.push_back(addr);
    }
    return clients;
}

void GameServer::handleNewClient(const net::Address& addr,
    uint32_t current_time) {
    ClientInfo info;
    info.address = addr;
    info.last_packet_time = current_time;
    _clients[addr] = info;

    std::cout << "[GameServer] New client connected: "
              << addr.getIP() << ":" << addr.getPort() << std::endl;

    if (_on_client_connect) {
        _on_client_connect(addr);
    }
}

void GameServer::queueIncomingPackets(
    const std::vector<std::vector<uint8_t>>& packets,
    const net::Address& sender) {
    std::lock_guard<std::mutex> lock(_incoming_mutex);
    for (const auto& packet_data : packets) {
        if (!packet_data.empty()) {
            IncomingPacket pkt;
            pkt.data = packet_data;
            pkt.sender = sender;
            _incoming_packets.push(pkt);
        }
    }
}

void GameServer::receiveUDP() {
    std::vector<net::Address> senders = udpReceive(0, 100);
    uint32_t current_time = getCurrentTimeMs();

    for (const net::Address& sender : senders) {
        auto packets = unpack(sender, -1);

        std::cout << "[GameServer] Received " << packets.size()
                  << " packet(s) from " << sender.getIP() << ":"
                  << sender.getPort() << std::endl;

        auto it = _clients.find(sender);
        if (it == _clients.end()) {
            handleNewClient(sender, current_time);
        } else {
            it->second.last_packet_time = current_time;
        }

        queueIncomingPackets(packets, sender);
    }
}

void GameServer::receiveTCP() {
    uint32_t current_time = getCurrentTimeMs();

    net::Address client_addr;
    int new_fd = acceptClient(client_addr, current_time);
    while (new_fd > 0) {
        handleNewClient(client_addr, current_time);
        _address_to_fd[client_addr] = new_fd;
        std::cout << "  (fd: " << new_fd << ")" << std::endl;
        new_fd = acceptClient(client_addr, current_time);
    }

    std::vector<int> ready_fds = tcpReceive(0);
    for (int fd : ready_fds) {
        std::optional<net::Address> client_addr_opt;
        for (const auto& [addr, client_fd] : _address_to_fd) {
            if (client_fd == fd) {
                client_addr_opt = addr;
                break;
            }
        }
        if (!client_addr_opt.has_value())
            continue;

        const net::Address& client_address = client_addr_opt.value();
        auto packets = unpack(client_address, -1);
        if (!packets.empty()) {
            std::cout << "[GameServer] Received " << packets.size()
                      << " packet(s) from " << client_address.getIP() << ":"
                      << client_address.getPort() << std::endl;
            auto it = _clients.find(client_address);
            if (it != _clients.end()) {
                it->second.last_packet_time = current_time;
            }
            queueIncomingPackets(packets, client_address);
        }
    }
}

void GameServer::processOutgoingPackets() {
    std::lock_guard<std::mutex> lock(_outgoing_mutex);
    while (!_outgoing_packets.empty()) {
        OutgoingPacket& packet = _outgoing_packets.front();

        try {
            if (packet.is_broadcast) {
                for (const auto& [addr, info] : _clients) {
                    sendTo(addr, packet.data);
                }
            } else {
                sendTo(packet.client, packet.data);
            }
        } catch (const std::exception& e) {
            std::cerr << "[GameServer] Send error: " << e.what() << std::endl;
        }

        _outgoing_packets.pop();
    }
}

void GameServer::checkClientTimeouts() {
    const uint32_t timeout_ms = 30000;  // 30 seconds
    const uint32_t current_time = getCurrentTimeMs();

    std::vector<net::Address> to_remove;

    for (const auto& [addr, info] : _clients) {
        if (current_time - info.last_packet_time > timeout_ms) {
            to_remove.push_back(addr);
        }
    }

    for (const net::Address& addr : to_remove) {
        std::cout << "[GameServer] Client timeout: "
                  << addr.getIP() << ":" << addr.getPort() << std::endl;

        if (_on_client_disconnect) {
            _on_client_disconnect(addr);
        }
        _clients.erase(addr);
        _address_to_fd.erase(addr);
    }
}

uint32_t GameServer::getCurrentTimeMs() const {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch());
    return static_cast<uint32_t>(duration.count());
}

void GameServer::startNetworkThread() {
    if (_network_running) {
        std::cerr
            << "[GameServer] Network thread already running!" << std::endl;
        return;
    }

    _network_running = true;
    _network_thread = std::thread(&GameServer::networkThreadLoop, this);
    std::cout << "[GameServer] Network thread started" << std::endl;
}

void GameServer::stopNetworkThread() {
    if (!_network_running) {
        return;
    }

    _network_running = false;
    if (_network_thread.joinable()) {
        _network_thread.join();
    }
    std::cout << "[GameServer] Network thread stopped" << std::endl;
}

void GameServer::queuePacket(const net::Address& client,
    const std::vector<uint8_t>& data) {
    std::lock_guard<std::mutex> lock(_outgoing_mutex);
    OutgoingPacket packet;
    packet.data = data;
    packet.client = client;
    packet.is_broadcast = false;
    _outgoing_packets.push(packet);
}

void GameServer::queueBroadcast(const std::vector<uint8_t>& data) {
    std::lock_guard<std::mutex> lock(_outgoing_mutex);
    OutgoingPacket packet;
    packet.data = data;
    packet.is_broadcast = true;
    _outgoing_packets.push(packet);
}

void GameServer::networkThreadLoop() {
    std::cout << "[GameServer] Network thread loop started" << std::endl;

    while (_network_running) {
        try {
            if (_protocol_type == net::SocketType::UDP) {
                receiveUDP();
            } else {
                receiveTCP();
            }

            processOutgoingPackets();

            checkClientTimeouts();
        } catch (const std::exception& e) {
            std::cerr
                << "[GameServer] Network error: " << e.what() << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    std::cout << "[GameServer] Network thread loop ended" << std::endl;
}

}  // namespace network
}  // namespace te
