/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** AScene.hpp
*/

#ifndef ASCENE_HPP_
    #define ASCENE_HPP_

    #include <ECS/Registry.hpp>

    #include "scenes/IScene.hpp"

class AScene : public IScene {
    public:
        virtual void run(void) = 0;

    protected:
        ECS::Registry _reg;
};

#endif
