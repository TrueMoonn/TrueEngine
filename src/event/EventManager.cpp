/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** EventManager.cpp
*/

#include <ECS/Registry.hpp>

#include "event/EventManager.hpp"
#include "event/events.hpp"

namespace te {
namespace event {

EventManager::EventManager(pollFunc func) : _pollFunc(func) {}

void EventManager::setPollFunc(pollFunc func) {
    _pollFunc = func;
}

void EventManager::pollEvents(ECS::Registry& reg) {
    if (_pollFunc)
        _pollFunc(_events, reg);
}

void EventManager::addSubscription(System sys, eventFunc func) {
    _subscription[sys].push_back(func);
}

bool EventManager::isEvent(System sys) {
    return _events.systems.at(sys);
}

EventManager::eventContent EventManager::getEvent(System system) const {
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

void EventManager::emit(ECS::Registry& reg) {
    if (_events.keys.update) {
        for (const auto &func : _subscription[System::KeyPressed]) {
            func(reg, _events.keys);
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

}  // namespace event
}  // namespace te
