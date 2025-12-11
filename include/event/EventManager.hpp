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
    typedef std::variant<KeysEvent, MouseEvents, bool> eventContent;
    typedef std::function<void(ECS::Registry&, const eventContent&)> eventFunc;

 public:
    explicit EventManager() = default;
    explicit EventManager(pollFunc func);
    ~EventManager() = default;

    void setPollFunc(pollFunc func);
    void pollEvents(ECS::Registry& reg);

    bool isEvent(System sys);
    eventContent getEvent(System system) const;

    void addSubscription(System sys, eventFunc func);
    void emit(ECS::Registry& reg);

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
        {System::LIMITSYSTEM, {}}
    };
};

}  // namespace event
}  // namespace te
