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

namespace te {

typedef std::unordered_map<std::string, std::any> json_like;
typedef std::function<void(
    ECS::Registry&, const ECS::Entity&, const json_like&)> cmpt_builder;

typedef std::function<void(ECS::Registry&)> sys_builder;

class APlugin {
 public:
    explicit APlugin(ECS::Registry& reg);

    void createComponent(const std::string& name,
        const ECS::Entity& e, const json_like& json);

    void createSystem(const std::string& name);

 protected:
    std::unordered_map<std::string, cmpt_builder> _components;
    std::unordered_map<std::string, sys_builder> _systems;
 private:
    std::reference_wrapper<ECS::Registry> _reg;
};

}  // namespace te
