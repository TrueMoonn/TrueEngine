/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** EventManager.hpp
*/

#pragma once

    #include <utility>
    #include <tuple>
    #include <string>
    #include <unordered_map>
    #include <functional>
    #include <vector>
    #include <memory>

namespace te {

class SignalManager {
 public:
    using CallbackId = std::size_t;

 public:
    template<typename... Args, typename Func>
    CallbackId sub(const std::string& name, Func&& func) {
        if (_subs.find(name) == _subs.end()) {
            _subs.emplace(name, std::make_unique<SignalList<Args...>>());
        }
        auto* list = static_cast<SignalList<Args...>*>(
            _subs.at(name).get());

        CallbackId id = _next_callback_id++;
        list->callbacks.push_back({
            id,
            std::function<void(Args...)>(std::forward<Func>(func)),
            true
        });
        return id;
    }

    void enableCallback(CallbackId id) {
        for (auto& [name, signal_list] : _subs) {
            signal_list->enableCallback(id);
        }
    }

    void disableCallback(CallbackId id) {
        for (auto& [name, signal_list] : _subs) {
            signal_list->disableCallback(id);
        }
    }

    template<typename... Args>
    void emit(const std::string& name, Args&&... args) {
        if (_subs.find(name) == _subs.end())
            return;

        using DecayedArgs = std::tuple<std::decay_t<Args>...>;
        auto* list = static_cast<SignalList<std::decay_t<Args>...>*>(
            _subs.at(name).get());

        for (auto& callback : list->callbacks) {
            if (callback.enabled)
                callback.func(std::forward<Args>(args)...);
        }
    }

 private:
    struct ISignalList {
        virtual ~ISignalList() = default;
        virtual void enableCallback(CallbackId id) = 0;
        virtual void disableCallback(CallbackId id) = 0;
    };

    template<typename... Args>
    struct SignalList : ISignalList {
        struct Callback {
            CallbackId id;
            std::function<void(Args...)> func;
            bool enabled;
        };
        std::vector<Callback> callbacks;

        void enableCallback(CallbackId id) override {
            for (auto& cb : callbacks) {
                if (cb.id == id) {
                    cb.enabled = true;
                    break;
                }
            }
        }

        void disableCallback(CallbackId id) override {
            for (auto& cb : callbacks) {
                if (cb.id == id) {
                    cb.enabled = false;
                    break;
                }
            }
        }
    };

    std::unordered_map<std::string, std::unique_ptr<ISignalList>> _subs;
    CallbackId _next_callback_id = 0;
};

}  // namespace te
