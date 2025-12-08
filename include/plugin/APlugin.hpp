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
    #include "event/EventManager.hpp"

namespace te {
namespace plugin {

typedef std::function<void(
    ECS::Registry&, const ECS::Entity&, const toml::table&)> cmpt_builder;
typedef std::function<void(ECS::Registry&)> sys_builder;

/**
 * @brief Abstract class for Plugins factory
 * 
 * This class will be used as an Abstract class for futur plugins.
 * This class act as a factory to create Component or System to
 * the ECS::Registry
 * 
 */
class APlugin {
 public:
    APlugin(ECS::Registry&, event::EventManager&);

    /**
     * @brief Create a component directly to the ECS::Registry
     * 
     * @param name Name of the component
     * @param e ECS::Entity to load the component to
     * @param params toml::table parameter to create the component with 
     */
    void createComponent(const std::string& name,
        const ECS::Entity& e, const toml::table& params);
    /**
     * @brief Get every component names in the factory
     * 
     * @return a std::vector<std::string> fill with names of components
     */
    std::vector<std::string> getComponents(void) const;

    /**
     * @brief Create a system directly to the ECS::Registry
     * 
     * @param name Name of the system
     */
    void createSystem(const std::string& name);
    /**
     * @brief Get every systems names in the factory
     * 
     * @return a std::vector<std::string> fill with names of systems
     */
    std::vector<std::string> getSystems(void) const;

 protected:
    std::unordered_map<std::string, cmpt_builder> _components;
    std::unordered_map<std::string, sys_builder> _systems;

 private:
    std::reference_wrapper<event::EventManager> _events;
    std::reference_wrapper<ECS::Registry> _reg;
};

}  // namespace plugin
}  // namespace te
