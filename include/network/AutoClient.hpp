/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** AutoClient - Automatic network synchronization with ECS (client-side)
*/

#pragma once

#include <functional>
#include <map>
#include <string>
#include <cstdint>
#include <vector>

#include "GameClient.hpp"
#include <Network/Address.hpp>
#include "clock.hpp"

namespace ECS {
    class Registry;
}

namespace net {

/**
 * @brief Automatic client that syncs network state to ECS Registry
 *
 * AutoClient automatically:
 * - Receives game state from server (players, enemies, projectiles)
 * - Creates/updates/destroys entities in the ECS Registry
 * - Handles connection, login, lobby management
 * - Sends inputs to server
 *
 * The game logic remains in your systems - AutoClient only handles networking.
 */
class AutoClient : public te::network::GameClient {
 public:
    /**
     * @brief Construct an AutoClient with a reference to the game's Registry
     *
     * @param registry Reference to the ECS Registry containing game entities
     * @param protocol Network protocol ("UDP" or "TCP")
     */
    explicit AutoClient(ECS::Registry& registry,
        const std::string& protocol = "UDP");

    ~AutoClient() = default;

    /**
     * @brief Update the client (process incoming packets, update ECS)
     *
     * Call this in your game loop, typically once per frame.
     * Automatically updates ECS entities based on server data.
     *
     * @param delta_time Time elapsed since last update
     */
    void update(float delta_time);

    /**
     * @brief Connect to server and login with username
     *
     * @param server_ip Server IP address
     * @param port Server port
     * @param username Player username
     * @return true if connection successful
     */
    bool connectAndLogin(const std::string& server_ip, uint16_t port,
        const std::string& username);

    /**
     * @brief Logout and disconnect from server
     */
    void logoutAndDisconnect();

    /**
     * @brief Get the local player's ID (assigned by server after login)
     */
    std::uint32_t getMyPlayerId() const { return my_player_id; }

    /**
     * @brief Check if logged in successfully
     */
    bool isLoggedIn() const { return logged_in; }

    /**
     * @brief Send player inputs to server
     *
     * @param inputs Input string (e.g., "WASD" for movement)
     */
    void sendInputs(const std::string& inputs);

    /**
     * @brief Create a new lobby
     */
    void createLobby();

    /**
     * @brief Join an existing lobby
     *
     * @param lobby_code 6-character lobby code
     */
    void joinLobby(const std::string& lobby_code);

    /**
     * @brief Leave current lobby
     */
    void leaveLobby();

    /**
     * @brief Start game (admin only)
     */
    void startGame();

    /**
     * @brief Pause game (admin only)
     */
    void pauseGame();

    /**
     * @brief Called when successfully connected to server
     */
    void onConnected(std::function<void()> callback) {
        on_connected = callback;
    }

    /**
     * @brief Called when successfully logged in (receives player ID)
     */
    void onLoggedIn(std::function<void(std::uint32_t)> callback) {
        on_logged_in = callback;
    }

    /**
     * @brief Called when disconnected from server
     */
    void onDisconnected(std::function<void()> callback) {
        on_disconnected = callback;
    }

    /**
     * @brief Called when lobby is created (receives lobby code)
     */
    void onLobbyCreated(std::function<void(const std::string&)> callback) {
        on_lobby_created = callback;
    }

    /**
     * @brief Called when successfully joined a lobby
     */
    void onJoinedLobby(std::function<void()> callback) {
        on_joined_lobby = callback;
    }

    /**
     * @brief Called when game starts
     */
    void onGameStarting(std::function<void()> callback) {
        on_game_starting = callback;
    }

    /**
     * @brief Called when game ends
     */
    void onGameEnd(std::function<void()> callback) {
        on_game_end = callback;
    }

    /**
     * @brief Called when a new wave starts
     */
    void onNewWave(std::function<void(std::uint32_t)> callback) {
        on_new_wave = callback;
    }

    /**
     * @brief Called when local player dies
     */
    void onPlayerDead(std::function<void()> callback) {
        on_player_dead = callback;
    }

    std::function<void()> on_connected;
    std::function<void(std::uint32_t)> on_logged_in;
    std::function<void()> on_disconnected;
    std::function<void(const std::string&)> on_lobby_created;
    std::function<void()> on_joined_lobby;
    std::function<void()> on_game_starting;
    std::function<void()> on_game_end;
    std::function<void(std::uint32_t)> on_new_wave;
    std::function<void()> on_player_dead;

    std::function<void(std::uint32_t player_id, float x, float y)>
        on_player_discovered;

    std::function<void(std::uint32_t enemy_id, float x, float y)>
        on_enemy_discovered;

    std::function<void(std::uint32_t proj_id, float x, float y, uint8_t type)>
        on_projectile_discovered;

    std::map<std::uint32_t, std::uint32_t> player_id_to_entity;
    std::map<std::uint32_t, std::uint32_t> enemy_id_to_entity;
    std::map<std::uint32_t, std::uint32_t> projectile_id_to_entity;

 private:
    ECS::Registry& registry;

    bool logged_in;
    std::uint32_t my_player_id;
    std::string my_username;
    std::string current_lobby_code;

    std::uint32_t next_enemy_entity;
    std::uint32_t next_projectile_entity;

    void handleConnected(const std::vector<std::uint8_t>& data);
    void handleLoggedIn(const std::vector<std::uint8_t>& data);
    void handleLoggedOut(const std::vector<std::uint8_t>& data);
    void handlePlayersStates(const std::vector<std::uint8_t>& data);
    void handlePlayersInfo(const std::vector<std::uint8_t>& data);
    void handleEnemiesStates(const std::vector<std::uint8_t>& data);
    void handleEnemiesInfo(const std::vector<std::uint8_t>& data);
    void handleProjectilesPos(const std::vector<std::uint8_t>& data);
    void handleLobbyCreated(const std::vector<std::uint8_t>& data);
    void handleGameStarting(const std::vector<std::uint8_t>& data);
    void handleGameEnd(const std::vector<std::uint8_t>& data);
    void handleNewWave(const std::vector<std::uint8_t>& data);
    void handlePlayerDead(const std::vector<std::uint8_t>& data);
    void handlePong(const std::vector<std::uint8_t>& data);

    void cleanupOldEntities();
};

}  // namespace net
