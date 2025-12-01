/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** drawable.hpp
*/

#pragma once
#include <unordered_map>
#include <queue>

#include "components/position.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

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

    enum MouseButton {
        MouseLeft = 0,
        MouseRight,
        MouseMiddle,
        LIMITBUTTON,
    };

    static const std::unordered_map<sf::Mouse::Button, MouseButton> _Mouse = {{
        {sf::Mouse::Button::Left, MouseButton::MouseLeft},
        {sf::Mouse::Button::Right, MouseButton::MouseRight},
        {sf::Mouse::Button::Middle, MouseButton::MouseMiddle},
    }};

    struct Event {
        explicit Event() {
            std::fill(std::begin(this->_Keys), std::end(this->_Keys), false);
            std::fill(std::begin(this->_Systems), std::end(this->_Systems), false);
        };

        
        std::array<bool, Key::LIMITKEY> _Keys;
        std::array<bool, System::LIMITSYSTEM> _Systems;
        std::array<std::pair<bool, Position2>, LIMITBUTTON> _MouseButtons;

    };
}