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

EventManager::EventManager() : _events(), _pollFunc(nullptr) {
    fillSubscriptions();
}

EventManager::EventManager(pollFunc func) : _events(), _pollFunc(func) {
    fillSubscriptions();
}

void EventManager::setPollFunc(pollFunc func) {
    _pollFunc = func;
}

void EventManager::pollEvents(ECS::Registry& reg) {
    if (_pollFunc)
        _pollFunc(_events, reg);
}

EventManager::eventContent EventManager::getEventContent(System system) const {
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

Events EventManager::getEvents(void) const {
    return _events;
}

bool EventManager::isEvent(System sys) const {
    if (sys == System::KeyPressed && _events.keys.update)
        return true;
    return _events.systems.at(sys);
}

void EventManager::setSystemEvent(System sys, bool val) {
    _events.systems.at(sys) = val;
}

void EventManager::addSubscription(System sys, eventFunc func) {
    _subscription[sys].push_back(func);
}

void EventManager::emit(ECS::Registry& reg,
    std::optional<ECS::Entity> target_entity) {
    if (_events.keys.update) {
        for (const auto &func : _subscription[System::KeyPressed]) {
            func(reg, _events.keys, target_entity);
        }
    }
    if (_events.mouses.update) {
        for (const auto &func : _subscription[System::MouseButtonPressed]) {
            func(reg, _events.mouses, target_entity);
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

void EventManager::fillSubscriptions(void) {
    for (std::size_t sys = Closed; sys < LIMITSYSTEM; ++sys) {
        _subscription[static_cast<System>(sys)] = {};
    }
}

}  // namespace event
}  // namespace te
