/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** AutoClient implementation - syncs network to ECS automatically
*/

#include <string>
#include <set>
#include <iostream>
#include <vector>

#include "network/AutoClient.hpp"
#include "Network/generated_messages.hpp"
#include "ECS/Registry.hpp"
#include "ECS/DenseSA.hpp"
#include "physic/components/position.hpp"
#include "physic/components/velocity.hpp"
#include "entity_spec/components/health.hpp"
#include "entity_spec/components/team.hpp"
#include "interaction/components/player.hpp"
#include "events.hpp"

namespace net {

AutoClient::AutoClient(ECS::Registry& reg, const std::string& protocol)
    : te::network::GameClient(protocol)
    , registry(reg)
    , logged_in(false)
    , my_player_id(0)
    , my_username("")
    , current_lobby_code("")
    , next_enemy_entity(1000)
    , next_projectile_entity(2000) {
    registerPacketHandler(1, [this](const std::vector<std::uint8_t>& data) {
        handleConnected(data);
    });

    registerPacketHandler(22, [this](const std::vector<std::uint8_t>& data) {
        handleLoggedIn(data);
    });

    registerPacketHandler(23, [this](const std::vector<std::uint8_t>& data) {
        handleLoggedOut(data);
    });

    registerPacketHandler(51, [this](const std::vector<std::uint8_t>& data) {
        handlePlayersStates(data);
    });

    registerPacketHandler(52, [this](const std::vector<std::uint8_t>& data) {
        handlePlayersInfo(data);
    });

    registerPacketHandler(55, [this](const std::vector<std::uint8_t>& data) {
        handleEnemiesStates(data);
    });

    registerPacketHandler(56, [this](const std::vector<std::uint8_t>& data) {
        handleEnemiesInfo(data);
    });

    registerPacketHandler(53, [this](const std::vector<std::uint8_t>& data) {
        handleProjectilesPos(data);
    });

    registerPacketHandler(33, [this](const std::vector<std::uint8_t>& data) {
        handleLobbyCreated(data);
    });

    registerPacketHandler(36, [this](const std::vector<std::uint8_t>& data) {
        handleGameStarting(data);
    });

    registerPacketHandler(49, [this](const std::vector<std::uint8_t>& data) {
        handleGameEnd(data);
    });

    registerPacketHandler(54, [this](const std::vector<std::uint8_t>& data) {
        handleNewWave(data);
    });

    registerPacketHandler(60, [this](const std::vector<std::uint8_t>& data) {
        handlePlayerDead(data);
    });

    registerPacketHandler(7, [this](const std::vector<std::uint8_t>& data) {
        handlePong(data);
    });
}

void AutoClient::update(float delta_time) {
    te::network::GameClient::update(delta_time);
    cleanupOldEntities();
}

bool AutoClient::connectAndLogin(const std::string& server_ip, uint16_t port,
    const std::string& username) {
    my_username = username;

    if (!connect(server_ip, port)) {
        std::cerr << "[AutoClient] Failed to connect to " << server_ip << ":"
            << port << std::endl;
        return false;
    }

    ::net::LOGIN login_msg;
    std::strncpy(login_msg.username, username.c_str(), 256);
    send(login_msg.serialize());
    return true;
}

void AutoClient::logoutAndDisconnect() {
    if (logged_in) {
        ::net::LOGOUT logout_msg;
        send(logout_msg.serialize());
    }

    disconnect();
    logged_in = false;
    my_player_id = 0;
}

void AutoClient::sendInputs(const te::Keys& keys) {
    if (!logged_in) {
        return;
    }

    ::net::CLIENT_INPUTS msg;
    msg.input_count = 102;
    for (uint32_t i = 0; i < 102; ++i) {
        msg.inputs[i] = keys[i] ? 1 : 0;
    }
    send(msg.serialize());
}

void AutoClient::createLobby() {
    if (!logged_in)
        return;

    ::net::CREATE_LOBBY msg;
    send(msg.serialize());
}

void AutoClient::joinLobby(const std::string& lobby_code) {
    if (!logged_in)
        return;

    ::net::JOIN_LOBBY msg;
    std::strncpy(msg.lobby_code, lobby_code.c_str(), 6);
    send(msg.serialize());
}

void AutoClient::leaveLobby() {
    if (!logged_in)
        return;

    ::net::LEAVE_LOBBY msg;
    send(msg.serialize());
}

void AutoClient::startGame() {
    if (!logged_in)
        return;

    ::net::ADMIN_START_GAME msg;
    send(msg.serialize());
}

void AutoClient::pauseGame() {
    if (!logged_in)
        return;

    ::net::ADMIN_PAUSE_GAME msg;
    send(msg.serialize());
}

void AutoClient::handleConnected(const std::vector<std::uint8_t>& data) {
    ::net::CONNECTED msg = ::net::CONNECTED::deserialize(data);

    if (on_connected) {
        on_connected();
    }
}

void AutoClient::handleLoggedIn(const std::vector<std::uint8_t>& data) {
    ::net::LOGGED_IN msg = ::net::LOGGED_IN::deserialize(data);

    my_player_id = msg.id;
    logged_in = true;

    // This prevents linking issues with plugin components
    /*
    try {
        std::uint32_t entity = my_player_id;

        registry.addComponent(entity, addon::intact::Player{my_player_id});
        registry.addComponent(entity, addon::physic::Position2(0.0f, 0.0f));
        registry.addComponent(entity, addon::physic::Velocity2(0.0f, 0.0f));
        registry.addComponent(entity, addon::eSpec::Health(100, 1.0f));
        registry.addComponent(entity, addon::eSpec::Team("player"));

        player_id_to_entity[my_player_id] = entity;

        std::cout << "[AutoClient] Created local player entity in ECS"
            << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[AutoClient] Failed to create player entity: "
            << e.what() << std::endl;
    }
    */

    if (on_logged_in) {
        on_logged_in(my_player_id);
    }
}

void AutoClient::handleLoggedOut(const std::vector<std::uint8_t>& data) {
    ::net::LOGGED_OUT msg = ::net::LOGGED_OUT::deserialize(data);

    std::uint32_t player_id = msg.id;

    auto it = player_id_to_entity.find(player_id);
    if (it != player_id_to_entity.end()) {
        try {
            registry.killEntity(it->second);
        } catch (const std::exception& e) {
            std::cerr << "[AutoClient] Failed to remove player entity: "
                << e.what() << std::endl;
        }
        player_id_to_entity.erase(it);
    }
}

void AutoClient::handlePlayersStates(const std::vector<std::uint8_t>& data) {
    if (data.size() < 5) {
        std::cerr << "[AutoClient] PLAYERS_STATES packet too small: "
            << data.size() << " bytes" << std::endl;
        return;
    }

    ::net::PLAYERS_STATES msg;
    try {
        msg = ::net::PLAYERS_STATES::deserialize(data);
    } catch (const std::exception& e) {
        std::cerr << "[AutoClient] Failed to deserialize PLAYERS_STATES: "
            << e.what() << std::endl;
        return;
    }

    for (const auto& player_state : msg.players) {
        std::uint32_t player_id = player_state.id;
        std::uint32_t entity;

        auto it = player_id_to_entity.find(player_id);
        if (it != player_id_to_entity.end()) {
            entity = it->second;
        } else {
            if (on_player_discovered) {
                on_player_discovered(player_id, player_state.x,
                    player_state.y);

                auto it2 = player_id_to_entity.find(player_id);
                if (it2 != player_id_to_entity.end()) {
                    entity = it2->second;

                } else {
                    std::cerr << "[AutoClient] WARNING: on_player_discovered "
                    << "didn't register entity for player "
                    << player_id << std::endl;
                    continue;
                }
            } else {
                continue;
            }
        }

        try {
            auto& positions =
                registry.getComponents<addon::physic::Position2>();
            auto& healths = registry.getComponents<addon::eSpec::Health>();

            if (PAGE(entity) >= positions.getSpar().size() ||
                PAGE_INDEX(entity) >=
                positions.getSpar()[PAGE(entity)].size()) {
                std::cerr << "[AutoClient] Player " << player_id << " entity "
                    << entity
                    << " out of bounds for position access" << std::endl;
                continue;
            }

            auto pos_opt =
                positions.getSpar()[PAGE(entity)][PAGE_INDEX(entity)];
            auto health_opt =
                healths.getSpar()[PAGE(entity)][PAGE_INDEX(entity)];

            if (pos_opt.has_value()) {
                auto& pos = GET_ENTITY_CMPT(positions, entity);
                pos.x = player_state.x;
                pos.y = player_state.y;
            } else {
                std::cerr << "[AutoClient] Player " << player_id
                    << " entity " << entity
                    << " has no Position component" << std::endl;
            }

            if (health_opt.has_value()) {
                auto& health = GET_ENTITY_CMPT(healths, entity);
                health.amount = static_cast<std::int64_t>(player_state.health);
            }
        } catch (const std::exception& e) {
            std::cerr << "[AutoClient] Exception updating player "
                << player_id << ": " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "[AutoClient] Unknown exception updating player "
                << player_id << std::endl;
        }
    }
}

void AutoClient::handlePlayersInfo(const std::vector<std::uint8_t>& data) {
    ::net::PLAYERS_INFO msg = ::net::PLAYERS_INFO::deserialize(data);

    // Update player info (weapon, level, status)
    // TODO(xxx): Implement when these components exist
}

void AutoClient::handleEnemiesStates(const std::vector<std::uint8_t>& data) {
    ::net::ENEMIES_STATES msg = ::net::ENEMIES_STATES::deserialize(data);

    std::set<std::uint32_t> current_enemies;
    for (const auto& enemy_state : msg.enemies) {
        current_enemies.insert(enemy_state.id);
    }

    std::vector<std::uint32_t> enemies_to_remove;
    for (const auto& [enemy_id, entity] : enemy_id_to_entity) {
        if (current_enemies.find(enemy_id) == current_enemies.end()) {
            enemies_to_remove.push_back(enemy_id);
        }
    }

    for (std::uint32_t enemy_id : enemies_to_remove) {
        std::uint32_t entity = enemy_id_to_entity[enemy_id];

        registry.killEntity(entity);
        enemy_id_to_entity.erase(enemy_id);
    }

    for (const auto& enemy_state : msg.enemies) {
        std::uint32_t enemy_id = enemy_state.id;
        std::uint32_t entity;

        auto it = enemy_id_to_entity.find(enemy_id);
        if (it != enemy_id_to_entity.end()) {
            entity = it->second;
        } else {
            if (on_enemy_discovered) {
                on_enemy_discovered(enemy_id, enemy_state.x, enemy_state.y);
                auto it2 = enemy_id_to_entity.find(enemy_id);
                if (it2 != enemy_id_to_entity.end()) {
                    entity = it2->second;
                } else {
                    std::cerr << "[AutoClient] WARNING: on_enemy_discovered "
                    << "didn't register entity for enemy " << enemy_id
                    << std::endl;
                    continue;
                }
            } else {
                continue;
            }
        }

        try {
            auto& positions =
                registry.getComponents<addon::physic::Position2>();
            auto& healths = registry.getComponents<addon::eSpec::Health>();

            if (PAGE(entity) >= positions.getSpar().size() ||
                PAGE_INDEX(entity) >=
                positions.getSpar()[PAGE(entity)].size()) {
                std::cerr << "[AutoClient] Enemy " << enemy_id << " entity "
                    << entity
                    << " out of bounds for position access" << std::endl;
                continue;
            }

            auto pos_opt =
                positions.getSpar()[PAGE(entity)][PAGE_INDEX(entity)];
            auto health_opt =
                healths.getSpar()[PAGE(entity)][PAGE_INDEX(entity)];

            if (pos_opt.has_value()) {
                auto& pos = GET_ENTITY_CMPT(positions, entity);
                pos.x = enemy_state.x;
                pos.y = enemy_state.y;
            } else {
                std::cerr << "[AutoClient] Enemy " << enemy_id << " entity "
                    << entity
                    << " has no Position component" << std::endl;
            }

            if (health_opt.has_value()) {
                auto& health = GET_ENTITY_CMPT(healths, entity);
                health.amount = static_cast<std::int64_t>(enemy_state.health);
            }
        } catch (const std::exception& e) {
            std::cerr << "[AutoClient] Exception updating enemy "
                << enemy_id << ": " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "[AutoClient] Unknown exception updating enemy "
                << enemy_id << std::endl;
        }
    }
}

void AutoClient::handleEnemiesInfo(const std::vector<std::uint8_t>& data) {
    ::net::ENEMIES_INFO msg = ::net::ENEMIES_INFO::deserialize(data);

    // Update enemy info (weapon, level, status)
    // TODO(xxx): Implement when these components exist
}

void AutoClient::handleProjectilesPos(const std::vector<std::uint8_t>& data) {
    ::net::PROJECTILES_POS msg = ::net::PROJECTILES_POS::deserialize(data);

    std::set<std::uint32_t> current_projectiles;
    for (const auto& proj : msg.projectiles) {
        current_projectiles.insert(proj.id);
    }

    std::vector<std::uint32_t> projectiles_to_remove;
    for (const auto& [proj_id, entity] : projectile_id_to_entity) {
        if (current_projectiles.find(proj_id) == current_projectiles.end()) {
            projectiles_to_remove.push_back(proj_id);
        }
    }

    for (std::uint32_t proj_id : projectiles_to_remove) {
        std::uint32_t entity = projectile_id_to_entity[proj_id];

        registry.killEntity(entity);
        projectile_id_to_entity.erase(proj_id);
    }

    for (const auto& proj : msg.projectiles) {
        std::uint32_t proj_id = proj.id;
        std::uint32_t entity;

        auto it = projectile_id_to_entity.find(proj_id);
        if (it != projectile_id_to_entity.end()) {
            entity = it->second;
        } else {
            if (on_projectile_discovered) {
                on_projectile_discovered(proj_id, proj.x, proj.y, proj.type);
                auto it2 = projectile_id_to_entity.find(proj_id);
                if (it2 != projectile_id_to_entity.end()) {
                    entity = it2->second;
                } else {
                    std::cerr
                        << "[AutoClient] WARNING: on_projectile_discovered "
                        << "didn't register entity for projectile "
                        << proj_id << std::endl;
                    continue;
                }
            } else {
                continue;
            }
        }

        try {
            auto& positions =
                registry.getComponents<addon::physic::Position2>();

            if (PAGE(entity) >= positions.getSpar().size() ||
                PAGE_INDEX(entity) >=
                positions.getSpar()[PAGE(entity)].size()) {
                std::cerr << "[AutoClient] Projectile " << proj_id
                    << " entity " << entity
                    << " out of bounds for position access" << std::endl;
                continue;
            }

            auto pos_opt =
                positions.getSpar()[PAGE(entity)][PAGE_INDEX(entity)];
            if (pos_opt.has_value()) {
                auto& pos = GET_ENTITY_CMPT(positions, entity);
                pos.x = proj.x;
                pos.y = proj.y;
            } else {
                std::cerr << "[AutoClient] Projectile " << proj_id
                    << " entity " << entity
                    << " has no Position component" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "[AutoClient] Exception updating projectile "
                << proj_id << ": " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "[AutoClient] Unknown exception updating projectile "
                << proj_id << std::endl;
        }
    }
}

void AutoClient::handleLobbyCreated(const std::vector<std::uint8_t>& data) {
    ::net::LOBBY_CREATED msg = ::net::LOBBY_CREATED::deserialize(data);

    current_lobby_code = std::string(msg.lobby_code, 6);

    if (on_lobby_created) {
        on_lobby_created(current_lobby_code);
    }
}

void AutoClient::handleGameStarting(const std::vector<std::uint8_t>& data) {
    std::cout << "[AutoClient] Game starting!" << std::endl;

    if (on_game_starting) {
        on_game_starting();
    }
}

void AutoClient::handleGameEnd(const std::vector<std::uint8_t>& data) {
    std::cout << "[AutoClient] Game ended" << std::endl;

    if (on_game_end) {
        on_game_end();
    }
}

void AutoClient::handleNewWave(const std::vector<std::uint8_t>& data) {
    ::net::NEW_WAVE msg = ::net::NEW_WAVE::deserialize(data);

    std::cout << "[AutoClient] New wave: " << msg.wave_id << std::endl;

    if (on_new_wave) {
        on_new_wave(msg.wave_id);
    }
}

void AutoClient::handlePlayerDead(const std::vector<std::uint8_t>& data) {
    std::cout << "[AutoClient] You died!" << std::endl;

    if (on_player_dead) {
        on_player_dead();
    }
}

void AutoClient::handlePong(const std::vector<std::uint8_t>& data) {
    // Pong received - could calculate latency here
}

void AutoClient::cleanupOldEntities() {
    // TODO(xxx): Implement cleanup of entities
    // that haven't been updated in a while
}

}  // namespace net
