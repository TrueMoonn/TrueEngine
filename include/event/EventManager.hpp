/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** EventManager.hpp
*/

#pragma once

    #include <unordered_map>
    #include <functional>
    #include <variant>
    #include <vector>

    #include <ECS/Registry.hpp>

    #include "event/events.hpp"

    #define POLL_EVENT_ENDPOINT "pollEvent"

namespace te {
namespace event {

class EventManager {
 public:
    typedef void(*pollFunc)(Events&, ECS::Registry&);
    typedef std::variant<KeysEvent, MouseEvent, bool> eventContent;
    typedef std::function<void(ECS::Registry&, const eventContent&)> eventFunc;

 public:
    explicit EventManager() = default;
    explicit EventManager(pollFunc func) : _pollFunc(func) {}
    ~EventManager() = default;

    void setPollFunc(pollFunc func) {
        _pollFunc = func;
    }
    void pollEvents(ECS::Registry& reg) {
        if (_pollFunc) {
            _pollFunc(_events, reg);
        }
    }

    void addSubscription(System sys, eventFunc func) {
        _subscription[sys].push_back(func);
    }

    bool isEvent(System sys) {
        return _events.systems.at(sys);
    }

    eventContent getEvent(System system) {
        if (system == System::KeyPressed || system == System::KeyReleased)
            return _events.keys;
        else if (system == System::MouseMoved
                || system == System::MouseWheelMoved
                || system == System::MouseWheelScrolled
                || system == System::MouseButtonPressed
                || system == System::MouseButtonReleased
                || system == System::MouseEntered
                || system == System::MouseQuit)
            return _events.mouses;
        else
            return _events.systems.at(system);
    }

    void updateScene(int scene) {
        _events.systems.at(System::ChangeScene) = true;
    }

    Events getEvent(void) {
        return _events;
    }

    void setEvent(System sys) {
        _events.systems.at(sys) = false;
    }

    void emit(ECS::Registry& reg) {
        if (_events.keys.update) {
            for (const auto &func : _subscription[System::KeyPressed]) {
                func(reg, _events.keys);
            }
        }
        if (_events.mouses.update) {
            for (const auto &func : _subscription[System::MouseButtonPressed]) {
                func(reg, _events.mouses);
                _events.mouses.clear();
            }
        }
        // for (auto& [sys, vect] : _subscription) {
        //     if (_events.systems[sys]) {
        //         for (const auto &func : vect) {
        //             func(reg, true);
        //         }
        //     }
        // }
    }

 private:
    pollFunc _pollFunc;

    Events _events;
    std::unordered_map<System, std::vector<eventFunc>> _subscription = {
        {System::Closed, {}},
        {System::Resized, {}},
        {System::LostFocus, {}},
        {System::GainedFocus, {}},
        {System::TextEntered, {}},
        {System::KeyPressed, {}},
        {System::KeyReleased, {}},
        {System::MouseWheelScrolled, {}},
        {System::MouseButtonPressed, {}},
        {System::MouseButtonReleased, {}},
        {System::MouseMoved, {}},
        {System::MouseEntered, {}},
        {System::MouseQuit, {}},
        {System::JoystickButtonPressed, {}},
        {System::JoystickButtonReleased, {}},
        {System::JoystickMoved, {}},
        {System::JoystickConnected, {}},
        {System::JoystickDisconnected, {}},
        {System::TouchBegan, {}},
        {System::TouchMoved, {}},
        {System::TouchEnded, {}},
        {System::SensorChanged, {}},
        {System::ChangeScene, {}},
        {System::LIMITSYSTEM, {}}
    };
};

}  // namespace event
}  // namespace te
