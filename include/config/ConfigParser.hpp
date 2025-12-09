/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** map.hpp
*/

#pragma once

    #include <vector>
    #include <string>
    #include <unordered_map>
    #include <toml++/toml.hpp>

    #include <ECS/Registry.hpp>

    #include "Exception.hpp"
    #include "plugin/PluginManager.hpp"

    #define MAP_LINE_DELIMITER_KEY '\n'
    #define MAP_TILE_DELIMITER_KEY ','
    #define MAP_LAYER_DELIMITER_KEY ':'
    #define MAP_CONFIG_DEFAULT_ENTITY_KEY " "

    #define CONFIG_ENTITIES_TABLE_NAME "ENTITIES"
    #define CONFIG_DEFAULT_ENTITY "DEFAULT"

    #define CONFIG_MAP_TABLE_NAME "MAP"

namespace te {

class ConfigParser {
 public:
    typedef std::string mentity_t;
    typedef std::vector<mentity_t> mtile_t;
    typedef std::vector<std::vector<mtile_t>> map_t;

    typedef std::unordered_map<std::string, toml::table> entityConfig;

 public:
    struct MapContent {
        map_t map;
        std::size_t layer_max;
        ECS::Entity size;
    };

    enum ContentType {
      MAP = 0,
      CONFIG
    };

 public:
    TE_EXCEPTION("ConfigParser", FileError)
    TE_EXCEPTION("ConfigParser", MapLoadingError)
    TE_EXCEPTION("ConfigParser", ConfigLoadingError)

 public:
   ConfigParser() = default;

    std::size_t parseFile(ContentType type, const std::string& path);
    entityConfig getConfig(std::size_t index) const;
    MapContent ConfigParser::getMap(std::size_t index) const;

 private:
    std::size_t eraseMap(std::size_t index);
    std::size_t eraseConfig(std::size_t index);
    std::size_t readMap(const std::string& raw);
    std::size_t readConfig(const std::string& raw);

    std::vector<entityConfig> _eConfigs;
    std::vector<MapContent> _maps;
};

}  // namespace te
