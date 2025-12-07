/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** GameClient.cpp - Generic game client implementation
*/

#include "network/GameClient.hpp"
#include <iostream>

namespace te {
namespace network {

GameClient::GameClient(ECS::Registry& ecs, const std::string& protocol)
    : _ecs(ecs)
    , _protocol_type(protocol == "TCP" ? SocketType::TCP : SocketType::UDP)
    , _connected(false) {
    _client = std::make_unique<Client>(protocol);
}

GameClient::~GameClient() {
    if (_connected) {
        disconnect();
    }
}

bool GameClient::connect(const std::string& server_ip, uint16_t port) {
    _server_address = Address(server_ip, port);
    try {
        if (_client->connect(server_ip, port)) {
            _client->setNonBlocking(true);
            _connected = true;
            std::cout << "[GameClient] Connected to " << server_ip << ":" << port << std::endl;

            if (_on_connect) {
                _on_connect();
            }

            return true;
        }
    } catch (const std::exception& e) {
        std::cerr << "[GameClient] Connection failed: " << e.what() << std::endl;
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
        auto packets = _client->receiveAll();
        for (const auto& packet_data : packets) {
            if (packet_data.empty())
                continue;
            if (_on_packet_received) {
                _on_packet_received(packet_data);
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

void GameClient::setPacketCallback(PacketCallback callback) {
    _on_packet_received = callback;
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
