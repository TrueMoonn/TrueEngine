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

class MapLoader {
    typedef std::string mentity_t;
    typedef std::vector<mentity_t> mtile_t;
    typedef std::vector<std::vector<mtile_t>> map_t;

 public:
    MapLoader(const ECS::Entity& first_entity, const ECS::Entity& max_entity);

    void loadMap(ECS::Registry& reg, const std::string& path);
    void clearMap(ECS::Registry& reg,
        ECS::Entity begin = 0, ECS::Entity size = 0);

 private:
    void readMap(const std::string& raw);
    void readConfig(const std::string& raw);
    void createEntity(const ECS::Entity& e, std::size_t x, std::size_t y,
        const toml::table& entity_info);
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