/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** events.hpp
*/

#pragma once

    #include <array>
    #include "maths/Vector.hpp"

namespace te {

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

typedef std::array<bool, Key::LIMITKEY> Keys;

enum MouseEvent {
    MouseLeft = 0,
    MouseRight,
    MouseMiddle,
    LIMITBUTTON,
};

struct Mouse {
    Mouse() : position(0, 0) {
        type.fill(false);
    }
    std::array<bool, MouseEvent::LIMITBUTTON> type;
    mat::Vector2i position;
};

}  // namespace te
