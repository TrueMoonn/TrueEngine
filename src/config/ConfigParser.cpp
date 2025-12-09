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

#include "config/ConfigParser.hpp"

namespace te {

std::size_t ConfigParser::parseFile(ContentType type,
    const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        throw ConfigParser::FileError("could not open file at '" + path + "'");
    std::stringstream buffer;
    buffer << file.rdbuf();
    if (type == ContentType::MAP)
        return readMap(buffer.str());
    else {
        return readConfig(buffer.str());
    }
}

ConfigParser::entityConfig ConfigParser::getConfig(std::size_t index) const {
    if (index < _eConfigs.size()) {
        return _eConfigs[index];
    }
    return ConfigParser::entityConfig();
}

ConfigParser::MapContent ConfigParser::getMap(std::size_t index) const {
    if (index < _maps.size()) {
        return _maps[index];
    }
    return ConfigParser::MapContent();
}

std::size_t ConfigParser::eraseMap(std::size_t index) {
    if (_maps.size() > index)
        _maps.erase(_maps.begin() + index);
    return _maps.size();
}

std::size_t ConfigParser::eraseConfig(std::size_t index) {
    if (_eConfigs.size() > index)
        _eConfigs.erase(_eConfigs.begin() + index);
    return _eConfigs.size();
}

std::size_t ConfigParser::readMap(const std::string& raw) {
    std::stringstream ss(raw);
    std::string raw_tiles;
    std::size_t map_size = 0;
    MapContent new_map;

    while (std::getline(ss, raw_tiles, MAP_LINE_DELIMITER_KEY)) {
        std::stringstream sss(raw_tiles);
        std::vector<mtile_t> tiles;
        std::string raw_tile;
        while (std::getline(sss, raw_tile, MAP_TILE_DELIMITER_KEY)) {
            std::stringstream ssss(raw_tile);
            mtile_t tile;
            mentity_t entity;
            while (std::getline(ssss, entity, MAP_LAYER_DELIMITER_KEY)) {
                if (!entity.compare(MAP_CONFIG_DEFAULT_ENTITY_KEY))
                    tile.push_back(CONFIG_DEFAULT_ENTITY);
                else
                    tile.push_back(entity);
                ++map_size;
            }
            if (tile.size() > new_map.layer_max)
                new_map.layer_max = tile.size();
            tiles.push_back(tile);
        }
        new_map.map.push_back(tiles);
    }
    new_map.size = map_size;
    _maps.push_back(new_map);
    return _maps.size();
}

std::size_t ConfigParser::readConfig(const std::string& raw) {
    toml::table config;
    entityConfig eConfig;
    try {
        config = toml::parse(raw);
    } catch (const toml::parse_error& err) {
        throw ConfigParser::ConfigLoadingError("toml::parse of config: " +
            std::string(err.what()));
    }
    toml::table *entities =
        config[CONFIG_ENTITIES_TABLE_NAME].as_table();
    if (entities == nullptr) {
        throw ConfigParser::ConfigLoadingError(
            std::string(CONFIG_ENTITIES_TABLE_NAME) +"  table not found");
    }
    for (auto &&[ename, entity] : *entities) {
        if (entity.is_table()) {
            eConfig[ename.data()] = *entity.as_table();
        }
    }
    if (config[CONFIG_MAP_TABLE_NAME].is_table()) {
        eConfig[CONFIG_MAP_TABLE_NAME] =
            *config[CONFIG_MAP_TABLE_NAME].as_table();
    }
    _eConfigs.push_back(eConfig);
    return _eConfigs.size();
}

}  // namespace te
