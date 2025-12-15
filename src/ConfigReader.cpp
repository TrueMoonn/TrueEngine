/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** ConfigReader.cpp
*/

#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

#include "ConfigReader.hpp"

namespace te {

void ConfigParser::addConfig(const std::string& path) {
    toml::table file;
    try {
        file = toml::parse_file(path);
    } catch (const toml::parse_error& err) {
        return;
    }
    readEntities(file);
}

std::size_t ConfigParser::addMap(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open())
        return 0;
    std::stringstream buffer;
    buffer << file.rdbuf();
    return readMap(buffer.str());
}

ConfigParser::eConfig ConfigParser::getConfig(void) const {
    return _eConfig;
}

ConfigParser::MapContent ConfigParser::getMap(std::size_t index) const {
    if (index < _maps.size()) {
        return _maps[index];
    }
    return MapContent();
}

toml::table ConfigParser::getEntityConfig(const std::string& name) const {
    if (_eConfig.find(name) != _eConfig.end())
        return _eConfig.at(name);
    return {};
}

void ConfigParser::readEntities(toml::table& table) {
    toml::table *entities = table[CONFIG_ENTITIES_TABLE_NAME].as_table();
    if (entities == nullptr)
        return;
    for (auto &&[name, entity] : *entities) {
        if (entity.is_table()) {
            if (_eConfig.find(name.data()) != _eConfig.end()) {
                for (auto &&[cname, content] : *entity.as_table()) {
                    _eConfig[name.data()].insert_or_assign(cname, content);
                }
            } else {
                _eConfig.insert_or_assign(name.data(), *entity.as_table());
            }
        }
    }
}

std::size_t ConfigParser::readMap(const std::string& raw) {
    MapContent map;
    for (auto& rawLine : optiSplit(raw, MAP_LINE_DELIMITER_KEY)) {
        std::vector<mtile_t> tiles;
        for (auto& rawTile : optiSplit(rawLine, MAP_TILE_DELIMITER_KEY)) {
            mtile_t tile;
            auto entities = optiSplit(rawTile, MAP_LAYER_DELIMITER_KEY);
            for (auto& entity : entities) {
                if (!entity.compare(MAP_DEFAULT_ENTITY_KEY))
                    tile.push_back(MAP_DEFAULT_ENTITY_NAME);
                else
                    tile.push_back(entity);
                ++map.size;
            }
            tiles.push_back(tile);
        }
        map.map.push_back(tiles);
    }
    _maps.push_back(map);
    return _maps.size() - 1;
}

std::vector<std::string> ConfigParser::optiSplit(
    const std::string& str, char sep) const {
    std::vector<std::string> results;
    std::string::const_iterator start = str.begin();
    std::string::const_iterator end = str.end();
    std::string::const_iterator next = std::find(start, end, sep);
    while (next != end) {
        results.push_back(std::string(start, next));
        start = next + 1;
        next = std::find(start, end, sep);
    }
    results.push_back(std::string(start, next));
    return results;
}

}  // namespace te
