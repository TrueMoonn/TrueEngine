#include <iostream>
#include <string>
#include <vector>
#include "network1/GameClient.hpp"
#include <Network/Client.hpp>

namespace te {
namespace network {

GameClient::GameClient(const std::string& protocol, const std::string& path)
    : net::Client(protocol, path) {
}

GameClient::~GameClient() {
    if (isConnected()) {
        disconnect();
    }
}

bool GameClient::connectToServer(const std::string& server_ip, uint16_t port) {
    try {
        if (connect(server_ip, port)) {
            setNonBlocking(true);
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

void GameClient::disconnectClient() {
    if (!isConnected())
        return;

    // Notify game
    if (_on_disconnect) {
        _on_disconnect();
    }

    std::cout << "[GameClient] Disconnected from server" << std::endl;
}

void GameClient::update(float delta_time) {
    if (!isConnected())
        return;
    try {
        // Receive data from server
        receiveFromServer(0, 10);

        // Extract and process packets from buffer
        auto packets = extractPacketsFromBuffer();
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

bool GameClient::sendToServer(const std::vector<uint8_t>& data) {
    if (!isConnected() || data.empty())
        return false;
    try {
        return send(data);
    } catch (const std::exception& e) {
        std::cerr << "[GameClient] Send failed: " << e.what() << std::endl;
        return false;
    }
}

void GameClient::receiveFromServer(int timeout, int maxInputs) {
    if (!isConnected())
        return;

    try {
        if (getProtocol() == net::SocketType::UDP) {
            udpReceive(timeout, maxInputs);
        } else {
            tcpReceive(timeout);
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

}  // namespace network
}  // namespace te
