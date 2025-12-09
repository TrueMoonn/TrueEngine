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
    GameServer(ECS::Registry& ecs, uint16_t port,
        const std::string& protocol = "UDP");
    ~GameServer();

    bool start();
    void stop();
    void update(float delta_time);

    // API for GAME LOGIC
    /**
     * @brief Send raw data to a specific client
     */
    bool sendTo(const net::Address& client, const std::vector<uint8_t>& data);

    /**
     * @brief Broadcast raw data to all clients (optionally exclude one)
     */
    void broadcastToAll(const std::vector<uint8_t>& data,
        const std::optional<net::Address>& exclude = std::nullopt);

    /**
     * @brief Receive data from clients (calls udpReceive or tcpReceive based on protocol)
     * This is a convenience wrapper that handles protocol-specific receive logic
     * @param timeout Timeout in milliseconds (0 for non-blocking)
     * @param maxInputs Maximum number of packets to receive (UDP only)
     */
    void receive(int timeout = 0, int maxInputs = 100);

    /**
     * @brief Callback type: called when data is received from a client
     * 
     * The game registers ONE callback that receives ALL data.
     * It's up to the game to dispatch based on packet type.
     */
    using PacketCallback = std::function<void(const std::vector<uint8_t>& data,
        const net::Address& sender)>;

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
     * @brief Callback: called when a client connects
     */
    using ClientConnectCallback =
        std::function<void(const net::Address& client)>;
    void setClientConnectCallback(ClientConnectCallback callback);

    /**
     * @brief Callback: called when a client disconnects or times out
     */
    using ClientDisconnectCallback =
        std::function<void(const net::Address& client)>;
    void setClientDisconnectCallback(ClientDisconnectCallback callback);

    // Server Info
    bool isRunning() const;
    size_t getClientCount() const;
    std::vector<net::Address> getConnectedClients() const;
    ECS::Registry& getECS() { return _ecs; }

 private:
    ECS::Registry& _ecs;
    std::unique_ptr<net::Server> _server;
    net::SocketType _protocol_type;
    uint16_t _port;
    bool _running;

    // Client tracking
    struct ClientInfo {
        net::Address address;
        uint32_t last_packet_time;
    };
    std::unordered_map<net::Address, ClientInfo> _clients;
    std::unordered_map<net::Address, int> _address_to_fd;  // For TCP

    // Game callbacks
    PacketCallback _on_packet_received;
    std::unordered_map<uint8_t, PacketCallback> _on_packet_received_map;
    ClientConnectCallback _on_client_connect;
    ClientDisconnectCallback _on_client_disconnect;

    void updateUDP(float delta_time);
    void updateTCP(float delta_time);
    void checkClientTimeouts();
    uint32_t getCurrentTimeMs() const;
};

}  // namespace network
}  // namespace te
