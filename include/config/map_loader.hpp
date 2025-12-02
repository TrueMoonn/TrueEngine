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
 * MAP - 
 * ENTITIES - 
 * 
 * Example file to parse:
 * ```text
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
 * ```
 */
class MapLoader {
    typedef std::string mentity_t;
    typedef std::vector<mentity_t> mtile_t;
    typedef std::vector<std::vector<mtile_t>> map_t;

 public:
    /**
     * @brief Construct a new Map Loader object
     * 
     * @param first_entity Set the first entity used as index to start
     * @param max_entity Set the number of entity used for a map
     */
    MapLoader(const ECS::Entity& first_entity, const ECS::Entity& max_entity);

    /**
     * @brief Load a map from a config file
     * 
     * @param reg The ECS registry to load the entities to
     * @param path The path to the config file
     */
    void loadMap(const std::string& path);
    /**
     * @brief Clear the map based on entity index
     * 
     * @param reg The ECS registry in wich we clear the entities
     * @param begin The index of the first entity to clear
     * @param size The number of entity to clear
     */
    void clearMap(ECS::Registry& reg,
        ECS::Entity begin = 0, ECS::Entity size = 0);

 private:
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
    /**
     * @brief Create a Entity object
     * 
     * This function use the PluginManager static class to create the
     * entity with the wanted parameters
     * 
     * @param e The entity to assign parameters
     * @param x The X tile position in the map
     * @param y The Y tile position in the map
     * @param entity_info The parameters to create the entity as parsed toml
     */
    void createEntity(const ECS::Entity& e, std::size_t x, std::size_t y,
        const toml::table& entity_info);
    /**
     * @brief Create a Map object
     * 
     * This function create the map based on what was parsed before
     * 
     */
    void createMap(void);

    map_t _map;
    std::size_t _layer_max = 0;
    std::unordered_map<mentity_t, toml::table> _entities;

    std::size_t _tilex;
    std::size_t _tiley;

    ECS::Entity _first;
    ECS::Entity _max;
};

}  // namespace te
