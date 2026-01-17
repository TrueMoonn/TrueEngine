/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** DlManager.cpp
*/

#include <string>
#include <iostream>
#include <vector>

#include "plugin/DlManager.hpp"

namespace te {
namespace plugin {

DlManager::~DlManager() {
    if (!_handles.empty())
        closeHandlers();
}

void DlManager::load(const std::string& path) {
    std::filesystem::path file(path);
#ifdef _WIN32
    if (file.extension() == ".dll")
        setHandler(file);
#else
    if (file.extension() == ".so")
        setHandler(file);
#endif
}

void DlManager::loadDirectory(const std::string& path) {
    for (const auto &file : std::filesystem::directory_iterator(path)) {
#ifdef _WIN32
        if (file.path().extension() == ".dll")
            setHandler(file);
#else
        if (file.path().extension() == ".so")
            setHandler(file);
#endif
    }
}

void DlManager::setHandler(const std::filesystem::path& path) {
#ifdef _WIN32
    HMODULE handle = LoadLibraryA(path.string().c_str());
    if (handle == NULL) {
        std::cerr << "Failed to load library: " << path << std::endl;
        return;
    }
#else
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (handle == NULL) {
        std::cerr << dlerror() << std::endl;
        return;
    }
#endif
    _handles[path.stem().string()] = handle;
}

std::vector<std::string> DlManager::getNames() const {
    std::vector<std::string> names;

    for (auto& [name, _] : _handles)
        names.push_back(name);
    return names;
}

void DlManager::closeHandlers(const std::string& id) {
    if (!id.empty()) {
        if (_handles.find(id) != _handles.end() && _handles.at(id)) {
#ifdef _WIN32
            FreeLibrary(_handles.at(id));
#else
            dlclose(_handles.at(id));
#endif
            _handles.erase(id);
        }
        return;
    }
    for (auto& [_, handle] : _handles) {
#ifdef _WIN32
        FreeLibrary(handle);
#else
        dlclose(handle);
#endif
    }
    _handles.clear();
}

}  // namespace plugin
}  // namespace te
