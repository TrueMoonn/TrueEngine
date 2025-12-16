#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <memory>
#include "network/GameServer.hpp"
#include <Network/PacketSerializer.hpp>

namespace te {
namespace network {

GameServer::GameServer(uint16_t port,
    const std::string& protocol)
    : _protocol_type(protocol == "TCP" ?
        net::SocketType::TCP : net::SocketType::UDP)
    , _port(port)
    , _running(false) {
    net::ProtocolManager proto;  // config/protocol.json
    _server = std::make_unique<net::Server>(protocol, port, proto);
}

GameServer::~GameServer() {
    if (_running) {
        stop();
    }
}

bool GameServer::start() {
    if (!_server->start()) {
        std::cerr << "[GameServer] Failed to start server" << std::endl;
        return false;
    }

    // Set non-blocking mode for UDP/TCP
    _server->setNonBlocking(true);

    _running = true;
    std::cout << "[GameServer] Server started on port " << _port << std::endl;
    return true;
}

void GameServer::stop() {
    _server->stop();
    _running = false;
    _clients.clear();
    std::cout << "[GameServer] Server stopped" << std::endl;
}

void GameServer::update(float delta_time) {
    if (!_running)
        return;

    if (_protocol_type == net::SocketType::UDP) {
        updateUDP(delta_time);
    } else {
        updateTCP(delta_time);
    }

    checkClientTimeouts();
}

bool GameServer::sendTo(const net::Address& client,
    const std::vector<uint8_t>& data) {
    if (!_running || data.empty())
        return false;

    try {
        if (_protocol_type == net::SocketType::UDP) {
            _server->udpSend(client, data);
        } else {
            auto it = _address_to_fd.find(client);
            if (it != _address_to_fd.end()) {
                _server->tcpSend(it->second, data);
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
            _server->udpReceive(timeout, maxInputs);
        } else {
            _server->tcpReceive(timeout);
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

void GameServer::updateUDP(float delta_time) {
    try {
        std::vector<net::Address> senders = _server->udpReceive(0, 100);
        for (const net::Address& sender : senders) {
            auto packets = _server->unpack(sender, -1);

            // Update or add client
            auto it = _clients.find(sender);
            if (it == _clients.end()) {
                // New client
                ClientInfo info;
                info.address = sender;
                info.last_packet_time = getCurrentTimeMs();
                _clients[sender] = info;
                std::cout << "[GameServer] New client connected: "
                          << sender.getIP() << ":" << sender.getPort()
                          << std::endl;
                // Notify game
                if (_on_client_connect) {
                    _on_client_connect(sender);
                }
            } else {
                it->second.last_packet_time = getCurrentTimeMs();
            }

            for (const auto& packet_data : packets) {
                if (packet_data.empty())
                    continue;
                uint8_t packet_code = packet_data[0];
                std::vector<uint8_t> payload(packet_data.begin() + 1,
                    packet_data.end());
                auto handler_it = _on_packet_received_map.find(packet_code);
                if (handler_it != _on_packet_received_map.end()) {
                    handler_it->second(payload, sender);
                } else {
                    std::cerr << "[GameServer] No handler registered for "
                              << "packet code: "
                              << static_cast<int>(packet_code) << " from "
                              << sender.getIP() << ":"
                              << sender.getPort() << std::endl;
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[GameServer] UDP update error: " << e.what() << std::endl;
    }
}

void GameServer::updateTCP(float delta_time) {
    try {
        uint32_t current_time = getCurrentTimeMs();
        net::Address client_addr;
        int new_fd = _server->acceptClient(client_addr, current_time);
        while (new_fd > 0) {
            ClientInfo info;
            info.address = client_addr;
            info.last_packet_time = current_time;
            _clients[client_addr] = info;
            _address_to_fd[client_addr] = new_fd;
            std::cout << "[GameServer] New TCP client connected: "
                      << client_addr.getIP() << ":" << client_addr.getPort()
                      << " (fd: " << new_fd << ")" << std::endl;
            if (_on_client_connect) {
                _on_client_connect(client_addr);
            }
            // Try to accept another client
            new_fd = _server->acceptClient(client_addr, current_time);
        }
        // Receive data from connected clients
        std::vector<int> ready_fds = _server->tcpReceive(0);
        for (int fd : ready_fds) {
            // Find the address for this fd
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
            auto packets = _server->unpack(client_address, -1);
            if (!packets.empty()) {
                auto it = _clients.find(client_address);
                if (it != _clients.end()) {
                    it->second.last_packet_time = current_time;
                }
                for (const auto& packet_data : packets) {
                    if (packet_data.empty())
                        continue;
                    uint8_t packet_code = packet_data[0];
                    std::vector<uint8_t> payload(packet_data.begin() + 1,
                        packet_data.end());
                    auto handler_it =
                        _on_packet_received_map.find(packet_code);
                    if (handler_it != _on_packet_received_map.end()) {
                        handler_it->second(payload, client_address);
                    } else {
                        std::cerr << "[GameServer] No handler registered for "
                                  << "packet code: "
                                  << static_cast<int>(packet_code) << " from "
                                  << client_address.getIP() << ":"
                                  << client_address.getPort() << std::endl;
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[GameServer] TCP update error: " << e.what() << std::endl;
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

}  // namespace network
}  // namespace te
