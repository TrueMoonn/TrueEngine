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

    #define TE_EXCEPTION(cName, eName) class eName : public Exception\
        {public: eName(const std::string& msg) : Exception(cName)\
        {_msg.append(msg);}};

namespace te {

class Exception : public std::exception {
 public:
    explicit Exception(const std::string& class_name) : _msg(PRE_MESSAGE) {
        _msg.append(class_name + ": ");
    }

    const char *what(void) const noexcept {
        return _msg.c_str();
    };

 protected:
    std::string _msg;
};

}  // namespace te
