/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** map_loader.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <toml++/toml.hpp>

#include "config/map_loader.hpp"

namespace te {

MapLoader::MapLoader(const ECS::Entity& first_entity,
    const ECS::Entity& max_entity) : _first(first_entity), _max(max_entity) {}

void MapLoader::loadMap(ECS::Registry& reg, const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw MapLoader::FileNotFound(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string map(buffer.str());
    std::size_t index_split = map.find(MAP_CONFIG_SPLIT_KEY);
    if (index_split == map.size())
        throw MapLoader::ParsingError("config separator '---' not found");
    readConfig(map.substr(index_split +
        std::strlen(MAP_CONFIG_SPLIT_KEY), map.size()));
    readMap(map.substr(0, index_split));
    createMap();
}

void MapLoader::clearMap(ECS::Registry& reg,
    ECS::Entity begin, ECS::Entity size) {
    if (size == 0) {
        begin = _first;
        size = _max;
    }
    for (ECS::Entity e = begin; e < size; ++e)
        reg.killEntity(e);
}

void MapLoader::readMap(const std::string& raw) {
    std::stringstream ss(raw);
    std::string raw_tiles;

    while (std::getline(ss, raw_tiles, MAP_LINE_DELIMITER_KEY)) {
        std::stringstream sss(raw_tiles);
        std::vector<mtile_t> tiles;
        std::string raw_tile;
        while (std::getline(sss, raw_tile, MAP_TILE_DELIMITER_KEY)) {
            std::stringstream ssss(raw_tile);
            mtile_t tile;
            mentity_t entity;
            while (std::getline(ssss, entity, MAP_LAYER_DELIMITER_KEY)) {
                if (!entity.compare(MAP_DEFAULT_ENTITY_KEY))
                    tile.push_back(MAP_CONFIG_DEFAULT_ENTITY);
                else
                    tile.push_back(entity);
            }
            if (tile.size() > _layer_max)
                _layer_max = tile.size();
            tiles.push_back(tile);
        }
        _map.push_back(tiles);
    }
}

void MapLoader::readConfig(const std::string& raw) {
    toml::table config;
    try {
        config = toml::parse(raw);
    } catch (const toml::parse_error& err) {
        throw MapLoader::ParsingError(err.what());
    }
    toml::table *entities =
        config[MAP_CONFIG_ENTITIES_TABLE_NAME].as_table();
    if (entities == nullptr)
        throw MapLoader::ParsingError("can't find ENTITY table");
    for (auto &&[ename, entity] : *entities) {
        if (entity.is_table()) {
            _entities[ename.data()] = *entity.as_table();
        }
    }
    _tilex = config["MAP"]["TILES"]["width"].value_or(50);
    _tiley = config["MAP"]["TILES"]["height"].value_or(50);
}

void MapLoader::createEntity(const ECS::Entity& e, std::size_t x,
    std::size_t y, const toml::table& entity_info) {
    toml::table pos;
    pos.insert("x", static_cast<float>(x *_tilex));
    pos.insert("y", static_cast<float>(y * _tiley));
    for (auto &&[cname, component] : entity_info) {
        if (!std::string(cname.data()).compare("position2")) {
            if (component.is_table()) {
                const toml::table& compTable = *component.as_table();
                pos.insert_or_assign("x", pos["x"].value<float>().value() +
                    compTable["x"].value<float>().value());
                pos.insert_or_assign("y", pos["y"].value<float>().value() +
                    compTable["y"].value<float>().value());
            }
            PluginManager::loadComponent(cname.data(), e, pos);
            continue;
        }
        if (component.is_table()) {
            const toml::table& compTable = *component.as_table();
            PluginManager::loadComponent(cname.data(), e, compTable);
        } else if (component.is_value()) {
            PluginManager::loadComponent(cname.data(), e);
        }
    }
}

void MapLoader::createMap(void) {
    ECS::Entity index_entity = _first;
    for (std::size_t layer = 0; layer < _layer_max; ++layer) {
        for (std::size_t y = 0; y < _map.size(); ++y) {
            for (std::size_t x = 0; x < _map[y].size(); ++x) {
                if (layer < _map[y][x].size()) {
                    createEntity(index_entity, x, y,
                        _entities.at(_map[y][x][layer]));
                    index_entity += 1;
                }
            }
        }
    }
}

}  // namespace te
