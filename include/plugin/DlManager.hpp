/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** DlManager.hpp
*/

#pragma once

    #include <dlfcn.h>
    #include <string>
    #include <unordered_map>
    #include <iostream>
    #include <filesystem>
    #include <optional>

namespace te {

class DlManager {
 public:
    DlManager();
    ~DlManager();

    void load(const std::string& path);
    void loadDirectory(const std::string& path);
    void clear(void);

    template <typename Symbol>
    Symbol access(const std::string& handle_name,
            const std::string& symbol_name) {
        for (auto& node : _handles) {
            if (!node.first.compare(handle_name)) {
                Symbol sym = (Symbol)dlsym(_handles.at(handle_name),
                    symbol_name.c_str());
                if (sym == nullptr) {
                    throw std::runtime_error(dlerror());
                }
                return sym;
            }
        }
        throw std::runtime_error("handler not found");
    }

 protected:
    void setHandler(const std::filesystem::path& path);
    void closeHandlers(const std::string& id = "");

    std::unordered_map<std::string, void *> _handles;
};

}  // namespace te
