#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "network/GameClient.hpp"


namespace te {
namespace network {

GameClient::GameClient(const std::string& protocol)
    : _protocol_type(protocol == "TCP" ?
        net::SocketType::TCP : net::SocketType::UDP)
    , _connected(false) {
    _client = std::make_unique<net::Client>(protocol);
}

GameClient::~GameClient() {
    if (_connected) {
        disconnect();
    }
}

bool GameClient::connect(const std::string& server_ip, uint16_t port) {
    _server_address = net::Address(server_ip, port);
    try {
        if (_client->connect(server_ip, port)) {
            _client->setNonBlocking(true);
            _connected = true;
            std::cout << "[GameClient] Connected to " <<
                server_ip << ":" << port << std::endl;

            if (_on_connect) {
                _on_connect();
            }

            return true;
        }
    } catch (const std::exception& e) {
        std::cerr <<
            "[GameClient] Connection failed: "
            << e.what() << std::endl;
    }
    return false;
}

void GameClient::disconnect() {
    if (!_connected)
        return;

    _connected = false;

    // Notify game
    if (_on_disconnect) {
        _on_disconnect();
    }

    std::cout << "[GameClient] Disconnected from server" << std::endl;
}

void GameClient::update(float delta_time) {
    if (!_connected)
        return;
    try {
        // Receive data from server
        receive(0, 10);

        // Extract and process packets from buffer
        auto packets = _client->extractPacketsFromBuffer();
        for (const auto& packet_data : packets) {
            if (packet_data.empty())
                continue;
            uint8_t packet_code = packet_data[0];
            std::vector<uint8_t> payload = packet_data;
            auto it = _on_packet_received_map.find(packet_code);
            if (it != _on_packet_received_map.end()) {
                it->second(payload);
            } else {
                std::cerr <<
                    "[GameClient] No handler registered for packet code: "
                    << static_cast<int>(packet_code)
                    << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "[GameClient] Update error: " << e.what() << std::endl;
    }
}

bool GameClient::send(const std::vector<uint8_t>& data) {
    if (!_connected || data.empty())
        return false;
    try {
        return _client->send(data);
    } catch (const std::exception& e) {
        std::cerr << "[GameClient] Send failed: " << e.what() << std::endl;
        return false;
    }
}

void GameClient::receive(int timeout, int maxInputs) {
    if (!_connected)
        return;

    try {
        if (_protocol_type == net::SocketType::UDP) {
            _client->udpReceive(timeout, maxInputs);
        } else {
            _client->tcpReceive(timeout);
        }
    } catch (const std::exception& e) {
        std::cerr << "[GameClient] Receive failed: " << e.what() << std::endl;
    }
}

void GameClient::registerPacketHandler(uint8_t key, PacketCallback callback) {
    _on_packet_received_map[key] = callback;
}

void GameClient::unregisterPacketHandler(uint8_t key) {
    _on_packet_received_map.erase(key);
}

void GameClient::setConnectCallback(ConnectCallback callback) {
    _on_connect = callback;
}

void GameClient::setDisconnectCallback(DisconnectCallback callback) {
    _on_disconnect = callback;
}

bool GameClient::isConnected() const {
    return _connected && _client && _client->isConnected();
}

}  // namespace network
}  // namespace te
