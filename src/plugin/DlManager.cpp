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
    if (file.extension() == ".so")
        setHandler(file);
}

void DlManager::loadDirectory(const std::string& path) {
    for (const auto &file : std::filesystem::directory_iterator(path)) {
        if (file.path().extension() == ".so")
            setHandler(file);
    }
}

void DlManager::setHandler(const std::filesystem::path& path) {
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (handle == NULL) {
        std::cerr << dlerror() << std::endl;
        return;
    }
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
            dlclose(_handles.at(id));
            _handles.erase(id);
        }
        return;
    }
    for (auto& [_, handle] : _handles)
        dlclose(handle);
    _handles.clear();
}

}  // namespace plugin
}  // namespace te
