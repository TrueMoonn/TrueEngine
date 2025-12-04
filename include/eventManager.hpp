/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Physic.hpp
*/

#pragma once

#include <unordered_map>
#include <functional>

#include "sfml/systems/event.hpp"



class eventManager {
    public:
        eventManager() = default;
        ~eventManager() = default;

        void addSubscription(te::System sys, std::function<void(void)> func) {this->_Event[sys].emplace_back(func);};
        void launchEvents(te::System sys) {for (const auto &func : this->_Event[sys]) {func();}};
    private:
        std::unordered_map<te::System, std::vector<std::function<void(void)>>> _Event = 
        {{te::System::Closed, {}}, // créer une fonction dans Gametool qui mets a true une variable qui arrete la boucle
         {te::System::Resized, {}},
         {te::System::LostFocus, {}},
         {te::System::GainedFocus, {}},
         {te::System::TextEntered, {}},
         {te::System::KeyPressed, {}},
         {te::System::KeyReleased, {}},
         {te::System::MouseWheelScrolled, {}},
         {te::System::MouseButtonPressed, {}},
         {te::System::MouseButtonReleased, {}},
         {te::System::MouseMoved, {}},
         {te::System::MouseEntered, {}},
         {te::System::MouseQuit, {}},
         {te::System::JoystickButtonPressed, {}},
         {te::System::JoystickButtonReleased, {}},
         {te::System::JoystickMoved, {}},
         {te::System::JoystickConnected, {}},
         {te::System::JoystickDisconnected, {}},
         {te::System::TouchBegan, {}},
         {te::System::TouchMoved, {}},
         {te::System::TouchEnded, {}},
         {te::System::SensorChanged, {}},
         {te::System::LIMITSYSTEM, {}}};
};