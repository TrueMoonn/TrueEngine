#pragma once

#include <memory>
#include <functional>
#include <vector>
#include <string>
#include <cstdint>
#include <unordered_map>

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
    /**
     * @brief Constructs a GameClient with the specified protocol
     * @param protocol Network protocol to use ("UDP" or "TCP"). Defaults to "UDP"
     */
    explicit GameClient(const std::string& protocol = "UDP");

    /**
     * @brief Destructor that ensures proper cleanup and disconnection
     */
    ~GameClient();

    /**
     * @brief Establishes a connection to the game server
     * @param server_ip IP address of the server to connect to
     * @param port Port number of the server
     * @return true if connection was successful, false otherwise
     */
    bool connect(const std::string& server_ip, uint16_t port);

    /**
     * @brief Disconnects from the server and cleans up resources
     */
    void disconnect();

    /**
     * @brief Updates the client state and processes network events
     * @param delta_time Time elapsed since last update in seconds
     */
    void update(float delta_time);

    /**
     * @brief Send raw data to the server
     * @param data Vector of bytes to send to the server
     * @return true if data was sent successfully, false otherwise
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
     * @brief Callback type: called when connection is established
     */
    using ConnectCallback = std::function<void()>;

    /**
     * @brief Sets the callback to be invoked when connection is established
     * @param callback Function to call upon successful connection
     */
    void setConnectCallback(ConnectCallback callback);

    /**
     * @brief Callback type: called on disconnection
     */
    using DisconnectCallback = std::function<void()>;

    /**
     * @brief Sets the callback to be invoked when disconnection occurs
     * @param callback Function to call upon disconnection
     */
    void setDisconnectCallback(DisconnectCallback callback);

    /**
     * @brief Checks if the client is currently connected to a server
     * @return true if connected, false otherwise
     */
    bool isConnected() const;

    /**
     * @brief Gets the address of the connected server
     * @return Reference to the server's network address
     */
    const net::Address& getServerAddress() const { return _server_address; }

 private:
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
