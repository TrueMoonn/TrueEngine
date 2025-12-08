#pragma once

#include <memory>
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <cstdint>

#include <ECS/Registry.hpp>
#include <Network/Server.hpp>
#include <Network/Address.hpp>

namespace te {
namespace network {

/**
 * @brief Generic multiplayer server
 * 
 * Provides networking with callbacks for the game to handle
 * packet logic, client connections, and disconnections.
 */
class GameServer {
 public:
    GameServer(ECS::Registry& ecs, uint16_t port, const std::string& protocol = "UDP");
    ~GameServer();

    bool start();
    void stop();
    void update(float delta_time);

    // API for GAME LOGIC
    /**
     * @brief Send raw data to a specific client
     */
    bool sendTo(const Address& client, const std::vector<uint8_t>& data);

    /**
     * @brief Broadcast raw data to all clients (optionally exclude one)
     */
    void broadcastToAll(const std::vector<uint8_t>& data, const Address* exclude = nullptr);

    /**
     * @brief Callback type: called when data is received from a client
     * 
     * The game registers ONE callback that receives ALL data.
     * It's up to the game to dispatch based on packet type.
     */
    using PacketCallback = std::function<void(const std::vector<uint8_t>& data, const Address& sender)>;
    void setPacketCallback(PacketCallback callback);

    /**
     * @brief Register a callback for a specific packet type
     * @param key The packet type identifier
     * @param callback Function to call when this packet type is received
     */
    void registerPacketHandler(const uint32_t& key, PacketCallback callback);

    /**
     * @brief Unregister a callback for a specific packet type
     * @param key The packet type identifier
     */
    void unregisterPacketHandler(const uint32_t& key);

    /**
     * @brief Callback: called when a client connects
     */
    using ClientConnectCallback = std::function<void(const Address& client)>;
    void setClientConnectCallback(ClientConnectCallback callback);

    /**
     * @brief Callback: called when a client disconnects or times out
     */
    using ClientDisconnectCallback = std::function<void(const Address& client)>;
    void setClientDisconnectCallback(ClientDisconnectCallback callback);

    // Server Info
    bool isRunning() const;
    size_t getClientCount() const;
    std::vector<Address> getConnectedClients() const;
    ECS::Registry& getECS() { return _ecs; }

 private:
    ECS::Registry& _ecs;
    std::unique_ptr<Server> _server;
    SocketType _protocol_type;
    uint16_t _port;
    bool _running;

    // Client tracking
    struct ClientInfo {
        Address address;
        uint32_t last_packet_time;
    };
    std::unordered_map<Address, ClientInfo> _clients;
    std::unordered_map<Address, int> _address_to_fd;  // For TCP

    // Game callbacks
    PacketCallback _on_packet_received;
    std::unordered_map<uint32_t, PacketCallback> _on_packet_received_map;
    ClientConnectCallback _on_client_connect;
    ClientDisconnectCallback _on_client_disconnect;

    void updateUDP(float delta_time);
    void updateTCP(float delta_time);
    void checkClientTimeouts();
    uint32_t getCurrentTimeMs() const;
};

}  // namespace network
}  // namespace te
