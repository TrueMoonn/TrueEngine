/*
** EPITECH PROJECT, 2025
** DeepestDungeon
** File description:
** map_reader.c++
*/

#include <vector>
#include <fstream>
#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Image.hpp>

#include "map_management.hpp"

#include "components/drawable.hpp"
#include "components/movable.hpp"
#include "components/position.hpp"
#include "components/sprite.hpp"
#include "components/hitbox.hpp"
#include "components/velocity.hpp"
#include "components/player.hpp"
#include "components/health.hpp"
#include "components/damage.hpp"
#include "components/interactive.hpp"

static void load_player(ECS::Registry& reg, const sf::Vector2u& pos) {
    reg.addComponent(MAP_ENTITY_PLAYER, te::Drawable());
    reg.addComponent(MAP_ENTITY_PLAYER, te::Health(10));
    reg.addComponent(MAP_ENTITY_PLAYER,
            te::Position2(pos.x * SQUARE_WIDTH, pos.y * SQUARE_HEIGHT));
    reg.addComponent(MAP_ENTITY_PLAYER, te::Sprite(TEXTURE_MAP.at(MAP_PLAYER)));
    reg.addComponent(MAP_ENTITY_PLAYER, te::Velocity2(0.0f, 0.0f));
    reg.addComponent(MAP_ENTITY_PLAYER, te::Player());
    reg.addComponent(MAP_ENTITY_PLAYER, te::Movable());
    reg.addComponent(MAP_ENTITY_PLAYER, te::Hitbox(0.0f, 0.0f, 30.0f, 30.0f));
    reg.addComponent(MAP_ENTITY_PLAYER,
        te::Interactive(-15.0f, -15.0f, 60.0f, 60.0f));
}

static void create_square(ECS::Registry& reg, const ECS::Entity& entity_id,
    char type, const sf::Vector2u& pos) {
    if (type == MAP_WALL) {
        reg.addComponent(entity_id, te::Drawable());
        reg.addComponent(entity_id, te::Damage(1));
        reg.addComponent(entity_id,
            te::Position2(pos.x * SQUARE_WIDTH, pos.y * SQUARE_HEIGHT));
        reg.addComponent(entity_id, te::Sprite(TEXTURE_MAP.at(MAP_WALL)));
        reg.addComponent(entity_id,
            te::Hitbox(0.0f, 0.0f, SQUARE_WIDTH, SQUARE_WIDTH));
    } else if (type == MAP_DOOR) {
        reg.addComponent(entity_id, te::Drawable());
        reg.addComponent(entity_id,
            te::Position2(pos.x * SQUARE_WIDTH, pos.y * SQUARE_HEIGHT));
        reg.addComponent(entity_id, te::Sprite(TEXTURE_MAP.at(MAP_DOOR)));
        reg.addComponent(entity_id,
            te::Hitbox(0.0f, 0.0f, SQUARE_WIDTH, SQUARE_WIDTH));
        reg.addComponent(entity_id,
            te::Interactive(-15.0f, -15.0f, 60.0f, 60.0f,
            [](ECS::Registry& reg) {
            reg.killEntity(MAP_ENTITY_PLAYER);
            for (ECS::Entity e = MAP_ENTITY_BACKGROUND;
                e < MAP_MAX_ENTITY_BACKGROUND; ++e) {
                reg.killEntity(e);
            }
            load_map(reg, MAPS_PATHS.at("test2"));
        }));
    } else if (type == MAP_PLAYER) {
        load_player(reg, pos);
    }
}

static void create_line(ECS::Registry& reg, ECS::Entity& entity_id,
    const std::string& line, size_t y) {
    for (size_t x = 0; x < line.size() && x < MAP_MAX_WIDTH; ++x) {
        create_square(reg, entity_id, line[x], sf::Vector2u(x, y));
        entity_id += 1;
    }
}

void load_map(ECS::Registry& reg, const std::string& path) {
    std::ifstream file(path);
    std::string line;
    std::vector<std::string> content;
    ECS::Entity entity_id = MAP_ENTITY_BACKGROUND;

    if (path.compare(path.size() - MAP_EXTENTION_SIZE - 1,
        MAP_EXTENTION_SIZE, MAP_EXTENTION)) {
        for (size_t y = 0; std::getline(file, line) &&
            y < MAP_MAX_HEIGHT; ++y) {
            create_line(reg, entity_id, line, y);
        }
    }
}
