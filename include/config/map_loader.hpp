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
    #include "plugin/PluginManager.hpp"

    #define MAP_CONFIG_SPLIT_KEY "\n---\n"
    #define MAP_LINE_DELIMITER_KEY '\n'
    #define MAP_TILE_DELIMITER_KEY ','
    #define MAP_LAYER_DELIMITER_KEY ':'

    #define MAP_DEFAULT_ENTITY_KEY " "
    #define MAP_CONFIG_DEFAULT_ENTITY "DEFAULT"

    #define MAP_CONFIG_ENTITIES_TABLE_NAME "ENTITIES"

namespace te {

/**
 * @brief Map Loader implementation for the True Engine
 * 
 * This class use an external library called toml++ to parse configuration files
 * It also use the ECS library to create entity directly to the Registry through
 * the PluginManager class
 * 
 * Example file to parse:
 * ```toml
 * X,X,X,X,X,X
 * X,G,G,G,G,X
 * X,G,G,G,G,X
 * X,G,G,G,G,X
 * X,G,G,G,G,X
 * X,X,X,X,X,X
 * ---
 * [MAP]
 *     [MAP.TILES]
 *     width = 50
 *     height = 50
 * [ENTITIES]
 *     [ENTITIES.X]
 *     [ENTITIES.G]
 * ```
 * @param MAP default table used to get base info of the map
 * @param ENTITIES default table for entities informations
 */
class MapLoader {
    typedef std::string mentity_t;
    typedef std::vector<mentity_t> mtile_t;
    typedef std::vector<std::vector<mtile_t>> map_t;

 public:
    struct MapContent {
        map_t map;
        std::unordered_map<std::string, toml::table> params;
        std::size_t layer_max;

        std::size_t tilex;
        std::size_t tiley;

        ECS::Entity size;

        void clear(void);
    };

 public:
    MapLoader() = default;

    /**
     * @brief Load a map from a config file
     * 
     * @param reg The ECS registry to load the entities to
     * @param path The path to the config file
     */
    void loadMap(const std::string& path);

    /**
     * @brief Get the Content object of the map
     * 
     * @return MapContent - Structure that will be use to build map entities
     */
    MapContent getContent(void) const; 

private:
    /**
     * @brief Clear the Content object of the map
     */
    void clearContent(void);
    /**
     * @brief Read the map and parse it
     * 
     * @param raw The map part of the raw file
     */
    void readMap(const std::string& raw);
    /**
     * @brief Read the conifg and parse it
     * 
     * @param raw The config part of the raw file
     */
    void readConfig(const std::string& raw);

    MapContent _content;
};

}  // namespace te
