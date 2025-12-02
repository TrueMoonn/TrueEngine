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
    #include <vector>
    #include <toml++/toml.hpp>

    #include <ECS/Registry.hpp>

namespace te {

typedef std::function<void(
    ECS::Registry&, const ECS::Entity&, const toml::table&)> cmpt_builder;
typedef std::function<void(ECS::Registry&)> sys_builder;

class APlugin {
 public:
    explicit APlugin(ECS::Registry& reg);

    void createComponent(const std::string& name,
        const ECS::Entity& e, const toml::table& json);
    std::vector<std::string> getComponents(void) const;

    void createSystem(const std::string& name);
    std::vector<std::string> getSystems(void) const;

 protected:
    std::unordered_map<std::string, cmpt_builder> _components;
    std::unordered_map<std::string, sys_builder> _systems;
 private:
    std::reference_wrapper<ECS::Registry> _reg;
};

}  // namespace te
