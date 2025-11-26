/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** DlManager.cpp
*/

#include <string>
#include <iostream>

#include "plugin/DlManager.hpp"

namespace te {

DlManager::DlManager() : _handles() {}

DlManager::~DlManager() {
    clear();
}

void DlManager::load(const std::string& path) {
    std::filesystem::path file(path);
    if (!std::filesystem::path(file).extension().compare(".so"))
        setHandler(file);
}

void DlManager::loadDirectory(const std::string& path) {
    for (const auto &file : std::filesystem::directory_iterator(path)) {
        if (!std::filesystem::path(file).extension().compare(".so"))
            setHandler(file);
    }
}

void DlManager::clear(void) {
    closeHandlers();
}

void DlManager::setHandler(const std::filesystem::path& path) {
    void *handle = NULL;
    handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
    if (handle == NULL) {
        std::cerr << dlerror() << std::endl;
        return;
    }
    _handles[path.stem()] = handle;
}

void DlManager::closeHandlers(const std::string& id) {
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

}  // namespace te
