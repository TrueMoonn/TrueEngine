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

void MapLoader::MapContent::clear(void) {
    map.clear();
    params.clear();
    layer_max = 0;
    tilex = 0;
    tiley = 0;
    size = 0;
}

void MapLoader::loadMap(const std::string& path) {
    clearContent();
    std::ifstream file(path);
    if (!file.is_open())
        throw MapLoader::LoadError("could not open map at '" + path + "'");
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string map(buffer.str());
    std::size_t index_split = map.find(MAP_CONFIG_SPLIT_KEY);
    if (index_split == map.npos)
        throw MapLoader::LoadError("could not find the split indicator");
    readConfig(map.substr(index_split +
        std::strlen(MAP_CONFIG_SPLIT_KEY), map.size()));
    readMap(map.substr(0, index_split));
}

MapLoader::MapContent MapLoader::getContent(void) const {
    return _content;
}

void MapLoader::clearContent() {
    _content.clear();
}

void MapLoader::readMap(const std::string& raw) {
    std::stringstream ss(raw);
    std::string raw_tiles;
    std::size_t map_size = 0;

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
                ++map_size;
            }
            if (tile.size() > _content.layer_max)
                _content.layer_max = tile.size();
            tiles.push_back(tile);
        }
        _content.map.push_back(tiles);
    }
    _content.size = map_size;
}

void MapLoader::readConfig(const std::string& raw) {
    toml::table config;
    try {
        config = toml::parse(raw);
    } catch (const toml::parse_error& err) {
        throw MapLoader::LoadError("toml::parse of config: " +
            std::string(err.what()));
    }
    toml::table *entities =
        config[MAP_CONFIG_ENTITIES_TABLE_NAME].as_table();
    if (entities == nullptr)
        throw MapLoader::LoadError(
            std::string(MAP_CONFIG_ENTITIES_TABLE_NAME) +"  table not found");
    for (auto &&[ename, entity] : *entities) {
        if (entity.is_table()) {
            _content.params[ename.data()] = *entity.as_table();
        }
    }
    _content.tilex = config["MAP"]["TILES"]["width"].value_or(50);
    _content.tiley = config["MAP"]["TILES"]["height"].value_or(50);
}

}  // namespace te
