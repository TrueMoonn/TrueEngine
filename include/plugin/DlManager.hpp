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
    DlManager() = default;
    ~DlManager() {
        closeHandlers();
    }

    void loadDirectory(const std::string& path) {
        for (const auto &file : std::filesystem::directory_iterator(path)) {
            if (!std::filesystem::path(file).extension().compare(".so"))
                setHandler(file);
        }
    }

    void load(const std::string& path) {
        std::filesystem::path file(path);
        if (!std::filesystem::path(file).extension().compare(".so"))
            setHandler(file);
    }

    void clear(void) {
        closeHandlers();
    }

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
    void setHandler(const std::filesystem::path& path) {
        void *handle = NULL;
        handle = dlopen(path.c_str(), RTLD_LAZY | RTLD_GLOBAL);
        if (handle == NULL) {
            std::cerr << dlerror() << std::endl;
            return;
        }
        _handles[path.stem()] = handle;
    }

    void closeHandlers(const std::string& id = "") {
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
    std::unordered_map<std::string, void *> _handles;
};

}  // namespace te
