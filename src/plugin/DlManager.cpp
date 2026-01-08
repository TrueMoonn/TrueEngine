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
#else
    if (file.extension() == ".so")
#endif
        setHandler(file);
}

void DlManager::loadDirectory(const std::string& path) {
    for (const auto &file : std::filesystem::directory_iterator(path)) {
#ifdef _WIN32
        if (file.path().extension() == ".dll")
#else
        if (file.path().extension() == ".so")
#endif
            setHandler(file);
    }
}

void DlManager::setHandler(const std::filesystem::path& path) {
#ifdef _WIN32
    HMODULE handle = LoadLibraryA(path.string().c_str());
    if (handle == NULL) {
        DWORD error = GetLastError();
        std::cerr << "Failed to load library: " << path.string() 
                  << ". Error code: " << error << std::endl;
        return;
    }
    _handles[path.stem().string()] = static_cast<void*>(handle);
#else
    void *handle = dlopen(path.c_str(), RTLD_LAZY);
    if (handle == NULL) {
        std::cerr << dlerror() << std::endl;
        return;
    }
    _handles[path.stem().string()] = handle;
#endif
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
            FreeLibrary(static_cast<HMODULE>(_handles.at(id)));
#else
            dlclose(_handles.at(id));
#endif
            _handles.erase(id);
        }
        return;
    }
    for (auto& [_, handle] : _handles) {
#ifdef _WIN32
        FreeLibrary(static_cast<HMODULE>(handle));
#else
        dlclose(handle);
#endif
    }
    _handles.clear();
}

}  // namespace plugin
}  // namespace te