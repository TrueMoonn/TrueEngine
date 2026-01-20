/*
** EPITECH PROJECT, 2025
** ECS
** File description:
** plugin_api.hpp
*/

#pragma once

#ifdef _WIN32
    #ifdef BUILDING_PLUGIN
        #define PLUGIN_API __declspec(dllexport)
    #else
        #define PLUGIN_API __declspec(dllimport)
    #endif
#else
    #define PLUGIN_API __attribute__((visibility("default")))
#endif
