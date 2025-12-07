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

    #include <ECS/Registry.hpp>

    #define POLL_EVENT_ENDPOINT "pollEvent"

namespace te {

/* KEYS */
enum Key {
    A = 0,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    num0,
    num1,
    num2,
    num3,
    num4,
    num5,
    num6,
    num7,
    num8,
    num9,
    Escape,
    LeftControl,
    LeftShift,
    LeftAlt,
    LeftSystem,
    RightControl,
    RightShift,
    RightAlt,
    RightSystem,
    Menu,
    LBracket,
    RBracket,
    Semicolon,
    Comma,
    Period,
    Apostrophe,
    Slash,
    Backslash,
    Grave,
    Equal,
    Hyphen,
    Space,
    Enter,
    Backspace,
    Tab,
    PageUp,
    PageDown,
    End,
    Home,
    Insert,
    Delete,
    Add,
    Subtract,
    Multiply,
    Divide,
    Left,
    Right,
    Up,
    Down,
    Numpad0,
    Numpad1,
    Numpad2,
    Numpad3,
    Numpad4,
    Numpad5,
    Numpad6,
    Numpad7,
    Numpad8,
    Numpad9,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    Pause,
    LIMITKEY,
};

typedef std::array<bool, Key::LIMITKEY> KeysEvent;

/* MOUSE */
enum MouseButton {
    MouseLeft = 0,
    MouseRight,
    MouseMiddle,
    LIMITBUTTON,
};

struct MouseInfo {
    bool active = false;
    float x;
    float y;
};

typedef std::array<MouseInfo, MouseButton::LIMITBUTTON> MouseEvents;

/* SYSTEM EVENTS */
enum System {
    Closed,
    Resized,
    LostFocus,
    GainedFocus,
    TextEntered,
    KeyPressed,
    KeyReleased,
    MouseWheelMoved,
    MouseWheelScrolled,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseEntered,
    MouseQuit,
    JoystickButtonPressed,
    JoystickButtonReleased,
    JoystickMoved,
    JoystickConnected,
    JoystickDisconnected,
    TouchBegan,
    TouchMoved,
    TouchEnded,
    SensorChanged,
    LIMITSYSTEM,
};

typedef std::array<bool, System::LIMITSYSTEM> SystemEvents;

struct Events {
    KeysEvent keys;
    MouseEvents mouses;
    SystemEvents systems;

    void clear() {
        keys.fill(false);
        mouses.fill(MouseInfo());
        systems.fill(false);
    }
};

class EventManager {
 public:
    typedef void(*pollFunc)(Events&, ECS::Registry&);
    typedef std::variant<KeysEvent, MouseEvents, bool> eventContent;
    typedef std::function<void(ECS::Registry&, const eventContent&)> eventFunc;

 public:
    EventManager() = default;
    EventManager(pollFunc func) : _pollFunc(func) {}
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
        _subscription[sys].emplace_back(func);
    };

    bool isEvent(System sys) {
        return _events.systems.at(sys);
    }
    void emit(ECS::Registry& reg) {
        for (auto& [sys, vect] : _subscription) {
            if (_events.systems[sys]) {
                for (const auto &func : vect) {
                    if (sys == System::KeyPressed) {
                        func(reg, _events.keys);
                    } else if (sys == System::MouseButtonPressed) {
                        func(reg, _events.mouses);
                    } else {
                        func(reg, true);
                    }
                }
            }
        }
    };

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

} // namespace te