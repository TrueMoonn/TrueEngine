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
typedef std::function<void(ECS::Registry&, const ECS::Entity&, const json_like&)> cmpt_builder;

typedef std::function<void(ECS::Registry&)> sys_builder;

class APlugin {
 public:
    APlugin(ECS::Registry& reg) : _reg(reg) {};

    void createComponent(const std::string& name,
        const ECS::Entity& e, const json_like& json) {
        if (_components.find(name) != _components.end())
            _components.at(name)(_reg, e, json);
        else
            std::cerr << "error(Plugin): can't find component" << std::endl;
    }

    void createSystem(const std::string& name) {
        if (_systems.find(name) != _systems.end())
            _systems.at(name)(_reg);
        else
            std::cerr << "error(Plugin): can't find system" << std::endl;
    }

 protected:
    std::unordered_map<std::string, cmpt_builder> _components = {};
    std::unordered_map<std::string, sys_builder> _systems = {};
 private:
    std::reference_wrapper<ECS::Registry> _reg;
};
