/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** map.hpp
*/

#pragma once

    #include <string>
    #include <map>
    #include <vector>
    #include <typeindex>
    #include <any>

namespace te {

template <class ...Components>
struct EntityBuilder {
    std::map<std::string, std::any> names;
};

struct MapLoader {
    MapLoader(const std::string& path, bool state);

    void changeMap(const std::string&);

    bool change;
    std::string fpath;
    std::map<char, EntityBuilder<std::any>> infos;
};

}  // namespace te
