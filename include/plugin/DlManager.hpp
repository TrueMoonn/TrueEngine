/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** DlManager.hpp
*/

#pragma once

#ifdef _WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include <string>
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include <optional>
#include <vector>

namespace te {
namespace plugin {

class DlManager {
 public:
    DlManager() = default;
    ~DlManager();

    void load(const std::string& path);
    void loadDirectory(const std::string& path);
    std::vector<std::string> getNames() const;
    void closeHandlers(const std::string& id = "");

    template <typename Symbol>
    Symbol access(const std::string& handName, const std::string& syName) {
        auto it = _handles.find(handName);
        if (it == _handles.end())
            throw std::runtime_error("handler not found");
#ifdef _WIN32
        void* sym = reinterpret_cast<void*>(GetProcAddress(
            static_cast<HMODULE>(it->second), syName.c_str()));
        if (sym == nullptr) {
            DWORD error = GetLastError();
            throw std::runtime_error("Symbol not found. Error code: "
                + std::to_string(error));
        }
#else
        dlerror();
        void* sym = dlsym(it->second, syName.c_str());
        if (sym == nullptr)
            throw std::runtime_error(dlerror());
#endif
        return reinterpret_cast<Symbol>(sym);
    }

 protected:
    void setHandler(const std::filesystem::path& path);

    std::unordered_map<std::string, void *> _handles;
};

}  // namespace plugin
}  // namespace te
