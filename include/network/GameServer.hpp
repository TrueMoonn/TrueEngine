#pragma once

#include <memory>
#include <unordered_map>
#include <functional>
#include <vector>
#include <string>
#include <cstdint>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>

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
    /**
     * @brief Constructs a GameServer with the specified port and protocol
     * @param port Port number on which the server will listen
     * @param protocol Network protocol to use ("UDP" or "TCP"). Defaults to "UDP"
     */
    explicit GameServer(uint16_t port, const std::string& protocol = "UDP");

    /**
     * @brief Destructor that ensures proper cleanup and shutdown
     */
    ~GameServer();

    /**
     * @brief Starts the server and begins listening for connections
     * @return true if server started successfully, false otherwise
     */
    bool start();

    /**
     * @brief Stops the server and disconnects all clients
     */
    void stop();

    /**
     * @brief Updates the server state and processes network events
     * @param delta_time Time elapsed since last update in seconds
     */
    void update(float delta_time);

    /**
     * @brief Send raw data to a specific client
     * @param client Address of the target client
     * @param data Vector of bytes to send
     * @return true if data was sent successfully, false otherwise
     */
    bool sendTo(const net::Address& client, const std::vector<uint8_t>& data);

    /**
     * @brief Broadcast raw data to all clients (optionally exclude one)
     * @param data Vector of bytes to broadcast
     * @param exclude Optional client address to exclude from broadcast
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
     * @brief Callback type: called when a client connects
     */
    using ClientConnectCallback =
        std::function<void(const net::Address& client)>;

    /**
     * @brief Sets the callback to be invoked when a client connects
     * @param callback Function to call when a new client connects
     */
    void setClientConnectCallback(ClientConnectCallback callback);

    /**
     * @brief Callback type: called when a client disconnects or times out
     */
    using ClientDisconnectCallback =
        std::function<void(const net::Address& client)>;

    /**
     * @brief Sets the callback to be invoked when a client disconnects
     * @param callback Function to call when a client disconnects or times out
     */
    void setClientDisconnectCallback(ClientDisconnectCallback callback);

    /**
     * @brief Checks if the server is currently running
     * @return true if server is running, false otherwise
     */
    bool isRunning() const;

    /**
     * @brief Gets the number of currently connected clients
     * @return Number of active client connections
     */
    size_t getClientCount() const;

    /**
     * @brief Gets a list of all connected client addresses
     * @return Vector containing addresses of all connected clients
     */
    std::vector<net::Address> getConnectedClients() const;

    /**
     * @brief Starts the network thread for asynchronous packet handling
     */
    void startNetworkThread();

    /**
     * @brief Stops the network thread
     */
    void stopNetworkThread();

    /**
     * @brief Queues a packet to be sent (thread-safe)
     * @param client Target client address
     * @param data Packet data to send
     */
    void queuePacket(const net::Address& client, const std::vector<uint8_t>& data);

    /**
     * @brief Queues a broadcast packet (thread-safe)
     * @param data Packet data to broadcast
     */
    void queueBroadcast(const std::vector<uint8_t>& data);

 private:
    std::unique_ptr<net::Server> _server;
    net::SocketType _protocol_type;
    uint16_t _port;
    bool _running;

    // Client tracking
    /**
     * @brief Structure containing information about a connected client
     */
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

    // Multithreading components
    std::thread _network_thread;
    std::atomic<bool> _network_running{false};

    // Thread-safe incoming packet queue (received from clients)
    struct IncomingPacket {
        std::vector<uint8_t> data;
        net::Address sender;
    };
    std::queue<IncomingPacket> _incoming_packets;
    std::mutex _incoming_mutex;

    // Thread-safe outgoing packet queue (server want to send)
    struct OutgoingPacket {
        std::vector<uint8_t> data;
        net::Address client;
        bool is_broadcast;
    };
    std::queue<OutgoingPacket> _outgoing_packets;
    std::mutex _outgoing_mutex;

    /**
     * @brief Network thread main loop
     */
    void networkThreadLoop();

    /**
     * @brief Handle a new client connection
     * @param addr Client address
     * @param current_time Current timestamp
     */
    void handleNewClient(const net::Address& addr, uint32_t current_time);

    /**
     * @brief Queue incoming packets for processing
     * @param packets List of packets
     * @param sender Sender address
     */
    void queueIncomingPackets(const std::vector<std::vector<uint8_t>>& packets,
        const net::Address& sender);

    /**
     * @brief Receive packets via UDP
     */
    void receiveUDP();

    /**
     * @brief Receive packets via TCP
     */
    void receiveTCP();

    /**
     * @brief Process and send all queued outgoing packets
     */
    void processOutgoingPackets();

    /**
     * @brief Checks for client timeouts and disconnects inactive clients
     */
    void checkClientTimeouts();

    /**
     * @brief Gets the current system time in milliseconds
     * @return Current time in milliseconds
     */
    uint32_t getCurrentTimeMs() const;
};

}  // namespace network
}  // namespace te
