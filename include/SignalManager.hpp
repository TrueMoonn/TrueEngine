/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** EventManager.hpp
*/

#pragma once

    #include <utility>
    #include <string>
    #include <unordered_map>
    #include <functional>
    #include <vector>
    #include <memory>

namespace te {

    class SignalManager {
     private:
        struct ISignalList {
            virtual ~ISignalList() = default;
        };

        template<typename... Args>
        struct SignalList : ISignalList {
            std::vector<std::function<void(Args...)>> callbacks;
        };

        std::unordered_map<std::string, std::unique_ptr<ISignalList>> _subs;

     public:
        template<typename... Args, typename Func>
        void sub(const std::string& name, Func&& func) {
            if (_subs.find(name) == _subs.end()) {
                _subs.emplace(name, std::make_unique<SignalList<Args...>>());
            }
            auto* list = static_cast<SignalList<Args...>*>(_subs.at(name).get());
            list->callbacks.push_back(std::function<void(Args...)>(std::forward<Func>(func)));
        }

        template<typename... Args>
        void emit(const std::string& name, Args&&... args) {
            if (_subs.find(name) == _subs.end())
                return;

            using DecayedArgs = std::tuple<std::decay_t<Args>...>;
            auto* list = static_cast<SignalList<std::decay_t<Args>...>*>(_subs.at(name).get());

            for (auto& callback : list->callbacks) {
                callback(std::forward<Args>(args)...);
            }
        }
    };

}  // namespace te
