/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** EventManager.hpp
*/

#pragma once

#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS)
    #include <print>
    #define DEBUG_SIG std::println
#else
    #define DEBUG_SIG(...) (void(0))
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
            DEBUG_SIG("Signal: Subscription: to '{}'", name);
            if (_subs.find(name) == _subs.end()) {
                DEBUG_SIG("Signal: Subscription: name not found");
                _subs.emplace(name, std::make_unique<SignalList<Args...>>());
                DEBUG_SIG("Signal: Subscription: new name emplaced OK");
            }
            auto* list = static_cast<SignalList<Args...>*>(
                _subs.at(name).get());
            list->callbacks.push_back(std::function<void(Args...)>(
                std::forward<Func>(func)));
            DEBUG_SIG("Signal: Subscription: subscription pushed back");
        }

        template<typename... Args>
        void emit(const std::string& name, Args&&... args) {
            DEBUG_SIG("Signal: Emition: emit signal '{}'", name);
            if (_subs.find(name) == _subs.end()) {
                DEBUG_SIG("Signal: Emition: name not found");
                return;
            }

            using DecayedArgs = std::tuple<std::decay_t<Args>...>;
            auto* list = static_cast<SignalList<std::decay_t<Args>...>*>(
                _subs.at(name).get());
#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS)
            std::size_t nb_emitions = 0;
#endif
            DEBUG_SIG("Signal: Emition: sending emition...");
            for (auto& callback : list->callbacks) {
#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS)
                nb_emitions += 1;
#endif
                callback(std::forward<Args>(args)...);
            }
#if defined(DEBUG_ALL) || defined(DEBUG_SIGNALS)
            DEBUG_SIG("Signal: Emition: {} emitions sent", nb_emitions);
#endif
        }
    };

}  // namespace te
