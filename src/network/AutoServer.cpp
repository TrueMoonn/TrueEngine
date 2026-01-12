/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** AutoServer implementation - automatically syncs ECS to network
*/

#include <iostream>
#include <cstring>
#include <random>
#include <vector>
#include <string>

#include "network/AutoServer.hpp"
#include "Network/generated_messages.hpp"
#include "ECS/Registry.hpp"
#include "ECS/DenseSA.hpp"
#include "ECS/DenseZipper.hpp"
#include "physic/components/position.hpp"
#include "entity_spec/components/health.hpp"
#include "entity_spec/components/team.hpp"
#include "interaction/components/player.hpp"
#include "events.hpp"

namespace net {

AutoServer::AutoServer(ECS::Registry& reg, te::SignalManager& sig,
    uint16_t port, const std::string& protocol)
    : te::network::GameServer(port, protocol)
    , registry(reg)
    , signals(sig)
    , next_player_id(2)
    , last_players_state_send(1.0f / 60.0f)
    , last_enemies_state_send(1.0f / 30.0f)
    , last_projectiles_send(1.0f / 60.0f)
    , last_players_info_send(1.0f / 10.0f)
    , last_enemies_info_send(1.0f / 10.0f)
    , players_state_interval(1.0f / 60.0f)
    , enemies_state_interval(1.0f / 30.0f)
    , projectiles_interval(1.0f / 60.0f)
    , players_info_interval(1.0f / 10.0f)
    , enemies_info_interval(1.0f / 10.0f)
    , default_spawn_x(100.0f)
    , default_spawn_y(100.0f)
    , default_player_health(100) {
    registerPacketHandler(20, [this](const std::vector<std::uint8_t>& data,
        const ::net::Address& sender) {
        handleLogin(data, sender);
    });

    registerPacketHandler(21, [this](const std::vector<std::uint8_t>& data,
        const ::net::Address& sender) {
        handleLogout(data, sender);
    });

    registerPacketHandler(32, [this](const std::vector<std::uint8_t>& data,
        const ::net::Address& sender) {
        handleCreateLobby(data, sender);
    });

    registerPacketHandler(30, [this](const std::vector<std::uint8_t>& data,
        const ::net::Address& sender) {
        handleJoinLobby(data, sender);
    });

    registerPacketHandler(35, [this](const std::vector<std::uint8_t>& data,
        const ::net::Address& sender) {
        handleAdminStartGame(data, sender);
    });

    registerPacketHandler(50, [this](const std::vector<std::uint8_t>& data,
        const ::net::Address& sender) {
        handleClientInputs(data, sender);
    });

    registerPacketHandler(6, [this](const std::vector<std::uint8_t>& data,
        const ::net::Address& sender) {
        handlePing(data, sender);
    });
}

void AutoServer::update(float delta_time) {
    static int update_count = 0;
    update_count++;
    if (update_count % 60 == 0) {
        std::cout << "[AutoServer] Update called " << update_count
            << " times" << std::endl;
    }

    te::network::GameServer::update(delta_time);

    if (last_players_state_send.checkDelay()) {
        sendPlayersStates();
    }

    if (last_enemies_state_send.checkDelay()) {
        sendEnemiesStates();
    }

    if (last_projectiles_send.checkDelay()) {
        sendProjectiles();
    }

    if (last_players_info_send.checkDelay()) {
        sendPlayersInfo();
    }

    if (last_enemies_info_send.checkDelay()) {
        sendEnemiesInfo();
    }
}

void AutoServer::handleLogin(const std::vector<std::uint8_t>& data,
    const ::net::Address& sender) {
    std::cout << "[AutoServer] *** RECEIVED LOGIN MESSAGE ***" << std::endl;

    ::net::LOGIN login_msg = ::net::LOGIN::deserialize(data);

    std::cout << "[AutoServer] Username: " << login_msg.username << std::endl;

    for (const auto& [addr, username] : logged_players) {
        if (username == login_msg.username) {
            ::net::USERNAME_ALREADY_TAKEN response;
            sendTo(sender, response.serialize());
            return;
        }
    }

    std::uint32_t player_id = next_player_id++;
    logged_players[sender] = login_msg.username;
    addr_to_player[sender] = player_id;
    player_to_addr[player_id] = sender;

    ::net::LOGGED_IN response;
    response.id = player_id;

    std::cout << "[AutoServer] Sending LOGGED_IN response to player '"
        << login_msg.username
        << "' (ID: " << player_id << ")" << std::endl;

    sendTo(sender, response.serialize());

    std::cout << "[AutoServer] Player '" << login_msg.username
        << "' logged in (ID: " << player_id << ")" << std::endl;

    // NOTE: Entity creation is handled by the game via on_player_login
    // This prevents linking issues with plugin components
    /*
    try {
        ECS::Entity entity = static_cast<ECS::Entity>(player_id);

        registry.addComponent(entity, addon::intact::Player{player_id});
        registry.addComponent(entity,
            addon::physic::Position2(default_spawn_x, default_spawn_y));
        registry.addComponent(entity, addon::physic::Velocity2(0.0f, 0.0f));
        registry.addComponent(entity,
            addon::eSpec::Health(default_player_health, 1.0f));
        registry.addComponent(entity, addon::eSpec::Team("player"));

        std::cout << "[AutoServer] Created player entity in ECS" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[AutoServer] Failed to create player entity: "
            << e.what() << std::endl;
    }
    */

    if (on_player_login) {
        on_player_login(player_id, login_msg.username);
    }

    std::cout << "[AutoServer] Sending initial PLAYERS_STATES to new client"
        << std::endl;
    sendPlayersStates();
}

void AutoServer::handleLogout(const std::vector<std::uint8_t>& data,
    const ::net::Address& sender) {
    auto it = addr_to_player.find(sender);
    if (it == addr_to_player.end()) {
        return;
    }

    std::uint32_t player_id = it->second;

    ::net::LOGGED_OUT msg;
    msg.id = player_id;
    broadcastToAll(msg.serialize());

    std::cout << "[AutoServer] Player " << player_id << " logged out"
        << std::endl;

    try {
        ECS::Entity entity = static_cast<ECS::Entity>(player_id);
        registry.killEntity(entity);
        std::cout << "[AutoServer] Removed player entity from ECS"
            << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[AutoServer] Failed to remove player entity: "
            << e.what() << std::endl;
    }

    player_to_addr.erase(player_id);
    addr_to_player.erase(sender);
    logged_players.erase(sender);

    if (on_player_logout) {
        on_player_logout(player_id);
    }
}

void AutoServer::handleCreateLobby(const std::vector<std::uint8_t>& data,
    const ::net::Address& sender) {
    std::string lobby_code = generateLobbyCode();

    ::net::LOBBY_CREATED response;
    std::strncpy(response.lobby_code, lobby_code.c_str(), 6);
    sendTo(sender, response.serialize());

    std::cout << "[AutoServer] Lobby created: " << lobby_code << std::endl;

    auto it = addr_to_player.find(sender);
    if (it != addr_to_player.end() && on_lobby_created) {
        on_lobby_created(it->second, lobby_code);
    }
}

void AutoServer::handleJoinLobby(const std::vector<std::uint8_t>& data,
    const ::net::Address& sender) {
    ::net::JOIN_LOBBY msg = ::net::JOIN_LOBBY::deserialize(data);

    std::cout << "[AutoServer] Player joined lobby: " << msg.lobby_code
        << std::endl;

    auto it = addr_to_player.find(sender);
    if (it != addr_to_player.end() && on_player_joined_lobby) {
        on_player_joined_lobby(it->second, msg.lobby_code);
    }
}

void AutoServer::handleAdminStartGame(const std::vector<std::uint8_t>& data,
    const ::net::Address& sender) {
    ::net::GAME_STARTING msg;
    broadcastToAll(msg.serialize());

    std::cout << "[AutoServer] Game starting" << std::endl;

    auto it = addr_to_player.find(sender);
    if (it != addr_to_player.end() && on_game_starting) {
        on_game_starting(it->second);
    }
}

void AutoServer::handleClientInputs(const std::vector<std::uint8_t>& data,
    const ::net::Address& sender) {
    ::net::CLIENT_INPUTS msg = ::net::CLIENT_INPUTS::deserialize(data);

    auto it = addr_to_player.find(sender);
    if (it == addr_to_player.end()) {
        return;
    }

    std::uint32_t player_id = it->second;

    te::Keys keys;
    for (uint32_t i = 0; i < 102 && i < msg.input_count; ++i) {
        keys[i] = (msg.inputs[i] != 0);
    }

    signals.emit("network_input", player_id, keys);

    if (on_client_inputs) {
        on_client_inputs(player_id, "");
    }
}

void AutoServer::handlePing(const std::vector<std::uint8_t>& data,
    const ::net::Address& sender) {
    ::net::PONG response;
    sendTo(sender, response.serialize());
}

void AutoServer::sendPlayersStates() {
    ::net::PLAYERS_STATES msg;

    try {
        auto& positions = registry.getComponents<addon::physic::Position2>();
        auto& healths = registry.getComponents<addon::eSpec::Health>();
        auto& players = registry.getComponents<addon::intact::Player>();

        for (auto&& [player, pos, health] :
            ECS::DenseZipper(players, positions, healths)) {
            ::net::PlayerState state;
            state.id = player.player;
            state.x = pos.x;
            state.y = pos.y;
            state.health = static_cast<double>(health.amount);
            state.shield = 0.0;  // TODO(xxx): implement later
            state.mana = 0.0;    // TODO(xxx): implement later

            msg.players.push_back(state);
        }
    } catch (...) {
        // Components not registered yet, skip this update
        return;
    }

    if (!msg.players.empty()) {
        broadcastToAll(msg.serialize());
    }
}

void AutoServer::sendEnemiesStates() {
    ::net::ENEMIES_STATES msg;

    try {
        auto& positions = registry.getComponents<addon::physic::Position2>();
        auto& healths = registry.getComponents<addon::eSpec::Health>();
        auto& teams = registry.getComponents<addon::eSpec::Team>();

        for (auto&& [entity_id, team, pos, health] :
            ECS::IndexedDenseZipper(teams, positions, healths)) {
            if (team.name == "player" || team.name == "Player") {
                continue;
            }

            if (team.name == "ally" || team.name == "Ally") {
                continue;
            }

            ::net::EnemyState state;
            state.id = static_cast<std::uint32_t>(entity_id);
            state.x = pos.x;
            state.y = pos.y;
            state.health = static_cast<double>(health.amount);
            state.shield = 0.0;
            state.mana = 0.0;

            msg.enemies.push_back(state);
        }
    } catch (...) {
        return;
    }

    if (!msg.enemies.empty()) {
        broadcastToAll(msg.serialize());
    }
}

void AutoServer::sendProjectiles() {
    ::net::PROJECTILES_POS msg;

    try {
        auto& positions = registry.getComponents<addon::physic::Position2>();
        auto& teams = registry.getComponents<addon::eSpec::Team>();
        auto& players = registry.getComponents<addon::intact::Player>();

        for (auto&& [entity_id, pos, team] :
            ECS::IndexedDenseZipper(positions, teams)) {
            if (players.hasComponent(entity_id)) {
                continue;
            }

            if (team.name == "ally" || team.name == "Ally") {
                ::net::Projectile proj;
                proj.id = static_cast<uint32_t>(entity_id);
                proj.type = 0;
                proj.x = pos.x;
                proj.y = pos.y;

                msg.projectiles.push_back(proj);
            }
        }
    } catch (...) {
        return;
    }

    if (!msg.projectiles.empty()) {
        broadcastToAll(msg.serialize());
    }
}

void AutoServer::sendPlayersInfo() {
    ::net::PLAYERS_INFO msg;

    try {
        auto& players = registry.getComponents<addon::intact::Player>();

        for (auto&& [player] : ECS::DenseZipper(players)) {
            ::net::PlayerInfo info;
            info.id = player.player;
            info.weapon = 0;   // TODO(xxx): implement later
            info.level = 1;    // TODO(xxx): implement later
            info.status = 0;   // TODO(xxx): implement later

            msg.players.push_back(info);
        }
    } catch (...) {
        return;
    }

    if (!msg.players.empty()) {
        broadcastToAll(msg.serialize());
    }
}

void AutoServer::sendEnemiesInfo() {
    ::net::ENEMIES_INFO msg;

    try {
        auto& positions = registry.getComponents<addon::physic::Position2>();
        auto& teams = registry.getComponents<addon::eSpec::Team>();

        for (auto&& [entity_id, team, pos] :
            ECS::IndexedDenseZipper(teams, positions)) {
            if (team.name == "player" || team.name == "Player") {
                continue;
            }

            ::net::EnemyInfo info;
            info.id = static_cast<std::uint32_t>(entity_id);
            info.weapon = 0;   // TODO(xxx): implement later
            info.level = 1;    // TODO(xxx): implement later
            info.status = 0;   // TODO(xxx): implement later

            msg.enemies.push_back(info);
        }
    } catch (...) {
        return;
    }

    if (!msg.enemies.empty()) {
        broadcastToAll(msg.serialize());
    }
}

void AutoServer::sendNewWave(std::uint32_t wave_id) {
    ::net::NEW_WAVE msg;
    msg.wave_id = wave_id;
    broadcastToAll(msg.serialize());
}

void AutoServer::sendGameDuration(std::uint32_t duration) {
    ::net::GAME_DURATION msg;
    msg.duration = duration;
    broadcastToAll(msg.serialize());
}

void AutoServer::sendGameLevel(std::uint32_t level) {
    ::net::GAME_LEVEL msg;
    msg.level = level;
    broadcastToAll(msg.serialize());
}

void AutoServer::sendGameEnd() {
    ::net::GAME_END msg;
    broadcastToAll(msg.serialize());
}

void AutoServer::sendPlayerDead(std::uint32_t player_id) {
    auto it = player_to_addr.find(player_id);
    if (it != player_to_addr.end()) {
        ::net::PLAYER_DEAD msg;
        sendTo(it->second, msg.serialize());
    }
}

std::string AutoServer::generateLobbyCode() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 35);

    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::string code;
    code.reserve(6);

    for (int i = 0; i < 6; ++i) {
        code += chars[dis(gen)];
    }

    return code;
}

void AutoServer::setPlayersStateFrequency(float frequency) {
    players_state_interval = frequency;
    last_players_state_send.delay = size_t(SEC_TO_MICRO(frequency));
}

void AutoServer::setEnemiesStateFrequency(float frequency) {
    enemies_state_interval = frequency;
    last_enemies_state_send.delay = size_t(SEC_TO_MICRO(frequency));
}

void AutoServer::setProjectilesFrequency(float frequency) {
    projectiles_interval = frequency;
    last_projectiles_send.delay = size_t(SEC_TO_MICRO(frequency));
}

void AutoServer::setPlayersInfoFrequency(float frequency) {
    players_info_interval = frequency;
    last_players_info_send.delay = size_t(SEC_TO_MICRO(frequency));
}

void AutoServer::setEnemiesInfoFrequency(float frequency) {
    enemies_info_interval = frequency;
    last_enemies_info_send.delay = size_t(SEC_TO_MICRO(frequency));
}

}  // namespace net
