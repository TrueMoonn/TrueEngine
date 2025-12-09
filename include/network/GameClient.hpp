#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>

#include <ECS/Registry.hpp>
#include <Network/Client.hpp>
#include <Network/Address.hpp>

namespace te {
namespace network {

/**
 * @brief Generic multiplayer client
 * 
 * Provides networking with callbacks for the game to handle
 * packet logic, connection events, and disconnections.
 */
class GameClient {
 public:
    explicit GameClient(ECS::Registry& ecs,
         const std::string& protocol = "UDP");
    ~GameClient();

    bool connect(const std::string& server_ip, uint16_t port);
    void disconnect();
    void update(float delta_time);

    // API for GAME LOGIC
    /**
     * @brief Send raw data to the server
     */
    bool send(const std::vector<uint8_t>& data);

    /**
     * @brief Receive data from server (calls udpReceive or tcpReceive based on protocol)
     * @param timeout Timeout in milliseconds (0 for non-blocking)
     * @param maxInputs Maximum number of packets to receive (UDP only)
     */
    void receive(int timeout = 0, int maxInputs = 10);

    /**
     * @brief Callback type: called when data is received from the server
     * 
     * The game registers callbacks for each type of packet.
     */
    using PacketCallback =
      std::function<void(const std::vector<uint8_t>& data)>;

    /**
     * @brief Register a callback for a specific packet type
     * @param key The packet type identifier (uint8_t code)
     * @param callback Function to call when this packet type is received
     */
    void registerPacketHandler(uint8_t key, PacketCallback callback);

    /**
     * @brief Unregister a callback for a specific packet type
     * @param key The packet type identifier (uint8_t code)
     */
    void unregisterPacketHandler(uint8_t key);

    /**
     * @brief Callback: called when connection is established
     */
    using ConnectCallback = std::function<void()>;
    void setConnectCallback(ConnectCallback callback);

    /**
     * @brief Callback: called on disconnection
     */
    using DisconnectCallback = std::function<void()>;
    void setDisconnectCallback(DisconnectCallback callback);

    // Client Info
    bool isConnected() const;
    const net::Address& getServerAddress() const { return _server_address; }
    ECS::Registry& getECS() { return _ecs; }

 private:
    ECS::Registry& _ecs;
    std::unique_ptr<net::Client> _client;
    net::SocketType _protocol_type;
    net::Address _server_address;
    bool _connected;

    // Game callbacks
    std::unordered_map<uint8_t, PacketCallback> _on_packet_received_map;
    ConnectCallback _on_connect;
    DisconnectCallback _on_disconnect;
};

}  // namespace network
}  // namespace te
