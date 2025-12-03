/*
** EPITECH PROJECT, 2025
** TrueEngine
** File description:
** Exception.hpp
*/

#pragma once

    #include <exception>
    #include <string>

    #define PRE_MESSAGE "error: "

namespace te {
   
class Exception : public std::exception {
 public:
    Exception() : _msg(PRE_MESSAGE) {}

    const char *what(void) const noexcept {
        return _msg.c_str();
    };

 protected:
    std::string _msg;
};

}  // namespace te

