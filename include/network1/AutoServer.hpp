/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** AutoServer - Automatic network synchronization with ECS
*/

#pragma once

#include <functional>
#include <map>
#include <vector>
#include <string>
#include <cstdint>

#include "GameServer.hpp"
#include <Network/Address.hpp>
#include "clock.hpp"
#include "SignalManager.hpp"

// Forward declaration
namespace ECS {
    class Registry;
}

namespace net {

/**
 * @brief Automatic server that reads from ECS and sync game state over network
 *
 * AutoServer automatically:
 * - Reads entities from the ECS Registry (players, enemies, projectiles)
 * - Constructs network messages (PLAYERS_STATES, ENEMIES_STATES, etc.)
 * - Sends them at configured frequencies
 * - Handles incoming client messages (LOGIN, INPUTS, etc.)
 *
 * The game logic remains in your systems - AutoServer only handles networking.
 */
class AutoServer : public te::network::GameServer {
 public:
    /**
     * @brief Construct an AutoServer with a reference to the game's Registry
     *
     * @param registry Reference to the ECS Registry containing game entities
     * @param signals Reference to the SignalManager for emitting input events
     * @param port Port to listen on
     * @param protocol Network protocol ("UDP" or "TCP")
     */
    AutoServer(ECS::Registry& registry, te::SignalManager& signals,
        uint16_t port, const std::string& protocol = "UDP");

    ~AutoServer() = default;

    /**
     * @brief Update the server (process incoming packets, send updates)
     *
     * Call this in your game loop, typically once per frame.
     * Override of GameServer::update() with automatic ECS synchronization.
     *
     * @param delta_time Time elapsed since last update
     */
    void update(float delta_time);

    /**
     * @brief Set how often to send PLAYERS_STATES (in seconds)
     */
    void setPlayersStateFrequency(float frequency);

    /**
     * @brief Set how often to send ENEMIES_STATES (in seconds)
     */
    void setEnemiesStateFrequency(float frequency);

    /**
     * @brief Set how often to send PROJECTILES_POS (in seconds)
     */
    void setProjectilesFrequency(float frequency);

    /**
     * @brief Set how often to send PLAYERS_INFO (in seconds)
     */
    void setPlayersInfoFrequency(float frequency);

    /**
     * @brief Set how often to send ENEMIES_INFO (in seconds)
     */
    void setEnemiesInfoFrequency(float frequency);

    /**
     * @brief Set default spawn position for new players
     */
    void setDefaultSpawnPosition(float x, float y) {
        default_spawn_x = x;
        default_spawn_y = y;
    }

    /**
     * @brief Set default health for new players
     */
    void setDefaultPlayerHealth(std::int64_t health) {
        default_player_health = health;
    }

    // ===== Callbacks =====

    /**
     * @brief Called when a client successfully logs in
     *
     * Use this to spawn a player entity in your ECS with the given player_id
     *
     * @param callback Function(player_id, username)
     */
    void onPlayerLogin(std::function<void(std::uint32_t,
        const std::string&)> callback) {
        on_player_login = callback;
    }

    /**
     * @brief Called when a client logs out
     *
     * Use this to remove the player entity from your ECS
     *
     * @param callback Function(player_id)
     */
    void onPlayerLogout(std::function<void(std::uint32_t)> callback) {
        on_player_logout = callback;
    }

    /**
     * @brief Called when client sends input data
     *
     * NOTE: AutoServer automatically emits "network_input" signal with
     * (player_id, inputs)
     * Use sub<uint32_t, te::Keys>("network_input", ...) to handle inputs
     * in your systems.
     * This callback is optional for additional custom logic.
     *
     * @param callback Function(player_id, inputs_string)
     */
    void onClientInputs(std::function<void(std::uint32_t,
        const std::string&)> callback) {
        on_client_inputs = callback;
    }

    /**
     * @brief Called when a lobby is created
     *
     * @param callback Function(player_id, lobby_code)
     */
    void onLobbyCreated(std::function<void(std::uint32_t,
        const std::string&)> callback) {
        on_lobby_created = callback;
    }

    /**
     * @brief Called when a player joins a lobby
     *
     * @param callback Function(player_id, lobby_code)
     */
    void onPlayerJoinedLobby(std::function<void(std::uint32_t,
        const std::string&)> callback) {
        on_player_joined_lobby = callback;
    }

    /**
     * @brief Called when admin starts the game
     *
     * @param callback Function(admin_player_id)
     */
    void onGameStarting(std::function<void(std::uint32_t)> callback) {
        on_game_starting = callback;
    }

    /**
     * @brief Manually send NEW_WAVE message
     */
    void sendNewWave(std::uint32_t wave_id);

    /**
     * @brief Manually send GAME_DURATION message
     */
    void sendGameDuration(std::uint32_t duration);

    /**
     * @brief Manually send GAME_LEVEL message
     */
    void sendGameLevel(std::uint32_t level);

    /**
     * @brief Manually send GAME_END message
     */
    void sendGameEnd();

    /**
     * @brief Send PLAYER_DEAD to a specific client
     */
    void sendPlayerDead(std::uint32_t player_id);

 private:
    ECS::Registry& registry;
    te::SignalManager& signals;

    std::uint32_t next_player_id;
    std::map<::net::Address, std::string> logged_players;
    std::map<::net::Address, std::uint32_t> addr_to_player;
    std::map<std::uint32_t, ::net::Address> player_to_addr;

    te::Timestamp last_players_state_send;
    te::Timestamp last_enemies_state_send;
    te::Timestamp last_projectiles_send;
    te::Timestamp last_players_info_send;
    te::Timestamp last_enemies_info_send;

    float players_state_interval;
    float enemies_state_interval;
    float projectiles_interval;
    float players_info_interval;
    float enemies_info_interval;

    float default_spawn_x;
    float default_spawn_y;
    std::int64_t default_player_health;

    std::function<void(std::uint32_t, const std::string&)> on_player_login;
    std::function<void(std::uint32_t)> on_player_logout;
    std::function<void(std::uint32_t, const std::string&)> on_client_inputs;
    std::function<void(std::uint32_t, const std::string&)> on_lobby_created;
    std::function<void(std::uint32_t, const std::string&)>
        on_player_joined_lobby;
    std::function<void(std::uint32_t)> on_game_starting;

    void handleLogin(const std::vector<std::uint8_t>& data,
        const ::net::Address& sender);
    void handleLogout(const std::vector<std::uint8_t>& data,
        const ::net::Address& sender);
    void handleCreateLobby(const std::vector<std::uint8_t>& data,
        const ::net::Address& sender);
    void handleJoinLobby(const std::vector<std::uint8_t>& data,
        const ::net::Address& sender);
    void handleAdminStartGame(const std::vector<std::uint8_t>& data,
        const ::net::Address& sender);
    void handleClientInputs(const std::vector<std::uint8_t>& data,
        const ::net::Address& sender);
    void handlePing(const std::vector<std::uint8_t>& data,
        const ::net::Address& sender);

    void sendPlayersStates();
    void sendEnemiesStates();
    void sendProjectiles();
    void sendPlayersInfo();
    void sendEnemiesInfo();

    std::string generateLobbyCode();
};

}  // namespace net
