/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** events.hpp
*/

#pragma once

    #include <array>

namespace te {
namespace event {

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

struct KeysEvent {
    bool update = false;
    std::array<bool, Key::LIMITKEY> keys = {false};
    void clear() {
        update = false;
        keys.fill(false);
    }
};

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

struct MouseEvent {
    bool update = false;
    std::array<MouseInfo, MouseButton::LIMITBUTTON> _MouseKey = {false};
    void clear() {
        update = false;
        _MouseKey.fill({false, 0, 0});
    }
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
    ChangeScene,
    LIMITSYSTEM,
};

typedef std::array<bool, System::LIMITSYSTEM> SystemEvents;

struct Events {
    KeysEvent keys;
    MouseEvent mouses;
    SystemEvents systems;

    void clear() {
        keys.clear();
        mouses.clear();
        systems.fill(false);
    }
};

}  // namespace event
}  // namespace te
