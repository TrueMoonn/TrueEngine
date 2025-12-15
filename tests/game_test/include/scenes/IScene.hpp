/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** IScene.hpp
*/

#pragma once

    #include "GameTool.hpp"

class IScene : public te::GameTool {
 public:
  virtual void run() = 0;
};
