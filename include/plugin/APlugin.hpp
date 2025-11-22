/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** APlugin.hpp
*/

#pragma once

    #include <unordered_map>
    #include <string>
    #include <functional>
    #include <any>
    #include <iostream>

    #include <ECS/Registry.hpp>

    #define DEFAULT_PLUGINS_RPATH "./plugins/" 
    
typedef std::unordered_map<std::string, std::any> json_like;
typedef std::function<void(const ECS::Entity&,
    ECS::Registry& reg, const json_like&)> build_func;

class APlugin {
 public:
    APlugin() = delete;
    APlugin(ECS::Registry&) {};

    template<class Component>
    void createComponent(const ECS::Entity& e, ECS::Registry& reg,
        const json_like& json) {
        if (_builders.find(typeid(Component)) != _builders.end())
            _builders.at(typeid(Component))(e, reg, json);
        else
            std::cerr << "error(Plugin): can't find component" << std::endl;
    }

 protected:
    std::unordered_map<std::type_index, build_func> _builders = {};
};
