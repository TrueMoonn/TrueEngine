/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** ConfigReader.hpp
*/

#pragma once

    #include <string>
    #include <vector>
    #include <unordered_map>
    #include <toml++/toml.hpp>

    #define CONFIG_ENTITIES_TABLE_NAME "ENTITIES"
    #define CONFIG_MAP_TABLE_NAME "MAP"

    #define CONFIG_MAP_TILE_DEFAULT_SIZE 50.f

    #define MAP_LINE_DELIMITER_KEY '\n'
    #define MAP_TILE_DELIMITER_KEY ','
    #define MAP_LAYER_DELIMITER_KEY ':'
    #define MAP_DEFAULT_ENTITY_KEY " "
    #define MAP_DEFAULT_ENTITY_NAME "DEFAULT"

namespace te {

class ConfigParser {
 public:
    typedef std::unordered_map<std::string, toml::table> eConfig;

    typedef std::string mentity_t;
    typedef std::vector<mentity_t> mtile_t;
    typedef std::vector<std::vector<mtile_t>> map_t;

    struct MapContent {
        map_t map;
        std::size_t size;
        std::size_t layer_max;
    };

 public:
    void addConfig(const std::string& path);
    std::size_t addMap(const std::string& path);

    eConfig getConfig(void) const;
    MapContent getMap(std::size_t index) const;

    toml::table getEntityConfig(const std::string& name) const;

 private:
    void readEntities(toml::table& table);
    eConfig _eConfig;

    std::size_t readMap(const std::string& raw);
    std::vector<MapContent> _maps;

    std::vector<std::string> optiSplit(
        const std::string& str, char sep) const;
};

}  // namespace te
