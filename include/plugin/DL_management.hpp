/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** DL_management.hpp
*/

#pragma once

    #include <dlfcn.h>
    #include <string>
    #include <functional>
    #include <unordered_map>
    #include <any>
    #include <iostream>
    #include <filesystem>
    #include <memory>
    #include <ECS/Entity.hpp>
    #include <ECS/Registry.hpp>

    #include "plugin/APlugin.hpp"

namespace te {

    #define ENDPOINT_NAME "get_pfactory"

    #define PLUGIN_RPATH "./plugins/"
    #define PLUGIN_R_PATH_LEN 10

    #define DL_SUF_LEN 3
    #define GET_PLUGIN_NAME(s) s.substr(PLUGIN_R_PATH_LEN, \
        s.size() - PLUGIN_R_PATH_LEN - DL_SUF_LEN)

class PluginManager {
    using maker = std::unique_ptr<APlugin>(*)(ECS::Registry&);
 public:
    PluginManager() = delete;
    PluginManager(const PluginManager&) = delete;
    ~PluginManager() {
        closeHandlers();
    }

    void operator=(const PluginManager&) = delete;

    static void load(ECS::Registry& reg) {
        for (const auto &file :
            std::filesystem::directory_iterator(PLUGIN_RPATH)) {
            if (!std::filesystem::path(file).extension().compare(".so"))
                setHandler(file.path(), reg);
        }
    }

    template<class Component>
    static void create(const std::string& facto,
        const ECS::Entity& e, ECS::Registry& reg, const json_like& json) {
        if (_factories.find(facto) != _factories.end())
            _factories.at(facto)->createComponent<Component>(e, reg, json);
    }

 protected:
    static void setHandler(const std::string& path, ECS::Registry& reg) {
        void *handle = NULL;
        handle = dlopen(path.c_str(), RTLD_LAZY);
        if (handle == NULL) {
            std::cerr << dlerror() << std::endl;
            return;
        }
        maker factory = (maker)dlsym(handle, ENDPOINT_NAME);
        if (factory == nullptr) {
            std::cerr << dlerror() << std::endl;
            dlclose(handle);
            return;
        }
        _factories[GET_PLUGIN_NAME(path)] = factory(reg);
        _handles[GET_PLUGIN_NAME(path)] = handle;
    }

    static void closeHandlers(const std::string& id = "") {
        if (!id.empty()) {
            if (_handles.find(id) != _handles.end() && _handles.at(id)) {
                dlclose(_handles.at(id));
                _handles.erase(id);
            }
            return;
        }
        for (auto& handle : _handles)
            dlclose(handle.second);
        _handles.clear();
    }

 private:
    static inline std::unordered_map<std::string, void *> _handles;
    static inline std::unordered_map<std::string,
        std::unique_ptr<APlugin>> _factories; 
};

}  // namespace te
