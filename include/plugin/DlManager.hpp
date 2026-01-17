/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** DlManager.hpp
*/

#pragma once

    #include <string>
    #include <unordered_map>
    #include <iostream>
    #include <filesystem>
    #include <optional>
    #include <vector>

#ifdef _WIN32
    #include <windows.h>
    typedef HMODULE DlHandle;
#else
    #include <dlfcn.h>
    typedef void* DlHandle;
#endif

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
        void* sym = reinterpret_cast<void*>(GetProcAddress(it->second, syName.c_str()));
        if (sym == nullptr)
            throw std::runtime_error("Failed to get symbol: " + syName);
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

    std::unordered_map<std::string, DlHandle> _handles;
};

}  // namespace plugin
}  // namespace te
