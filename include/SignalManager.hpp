/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** EventManager.hpp
*/

#pragma once

    #include <utility>
    #include <string>
    #include <vector>
    #include <unordered_map>
    #include <memory>
    #include <iostream>

    #include "Exception.hpp"

namespace te {

class SignalManager {
 public:
    TE_EXCEPTION("SignalManager", SignalNotFound)

 private:
    template<typename... Args>
    struct ISignal {
        virtual ~ISignal() = default;
        virtual void call(Args&&... args) = 0;
    };

    template<typename Func, typename... Args>
    struct ASignal : ISignal<Args...> {
        Func func;

        explicit ASignal(Func&& f) : func(std::forward<Func>(f)) {}

        void call(Args&&... args) override {
            func(std::forward<Args>(args)...);
        }
    };

    struct ISignalList {
        virtual ~ISignalList() = default;
    };

    template<typename... Args>
    struct SignalList : ISignalList {
        std::vector<std::unique_ptr<ISignal<Args...>>> signals;
    };

    std::unordered_map<std::string, std::unique_ptr<ISignalList>> _subs;

 public:
    template<typename... Args, typename Func>
    void sub(const std::string& name, Func&& func) {
        if (_subs.find(name) == _subs.end()) {
            _subs.emplace(name, std::make_unique<SignalList<Args...>>());
        }
        auto* list = static_cast<SignalList<Args...>*>(_subs.at(name).get());
        list->signals.push_back(std::make_unique<ASignal<Func, Args...>>(
            std::forward<Func>(func)));
    }

    template<typename... Args>
    void emit(const std::string& name, Args&&... args) {
        if (_subs.find(name) == _subs.end())
            return;
        auto* list = static_cast<SignalList<Args...>*>(_subs.at(name).get());
        for (auto& signal : list->signals) {
            signal->call(std::forward<Args>(args)...);
        }
    }
};

}  // namespace te
