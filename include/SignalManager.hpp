/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** EventManager.hpp
*/

#pragma once

#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS) ||\
    defined(DEBUG_SIGNALS_SUB) || defined(DEBUG_SIGNALS_EMIT)
    #include <print>
#endif

    #include <utility>
    #include <tuple>
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
#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS) || defined (DEBUG_SIGNALS_SUB)
            std::println("Signal: Subscription: to '{}'", name);
#endif
            if (_subs.find(name) == _subs.end()) {
#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS) || defined (DEBUG_SIGNALS_SUB)
                std::println("Signal: Subscription: name not found");
#endif
                _subs.emplace(name, std::make_unique<SignalList<Args...>>());
#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS) || defined (DEBUG_SIGNALS_SUB)
                std::println("Signal: Subscription: new name emplaced OK");
#endif
            }
            auto* list = static_cast<SignalList<Args...>*>(
                _subs.at(name).get());
            list->callbacks.push_back(std::function<void(Args...)>(
                std::forward<Func>(func)));
#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS) || defined (DEBUG_SIGNALS_SUB)
            std::println("Signal: Subscription: subscription pushed back");
#endif
        }

        template<typename... Args>
        void emit(const std::string& name, Args&&... args) {
#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS) || defined (DEBUG_SIGNALS_EMIT)
            std::println("Signal: Emition: emit signal '{}'", name);
#endif
            if (_subs.find(name) == _subs.end()) {
#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS) || defined (DEBUG_SIGNALS_EMIT)
            std::println("Signal: Emition: name not found");
#endif
                return;
            }

            using DecayedArgs = std::tuple<std::decay_t<Args>...>;
            auto* list = static_cast<SignalList<std::decay_t<Args>...>*>(
                _subs.at(name).get());
#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS) || defined (DEBUG_SIGNALS_EMIT)
            std::size_t nb_emitions = 0;
            std::println("Signal: Emition: sending emition...");
#endif
            for (auto& callback : list->callbacks) {
#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS) || defined (DEBUG_SIGNALS_EMIT)
                nb_emitions += 1;
#endif
                callback(std::forward<Args>(args)...);
            }
#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS) || defined (DEBUG_SIGNALS_EMIT)
            std::println("Signal: Emition: {} emitions sent", nb_emitions);
#endif
        }
    };

}  // namespace te
