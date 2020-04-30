//
// Created by lukas on 26.10.19.
//

#pragma once

#include <string>

class Logger {
public:
    static void debug(std::string message);
    static void message(std::string message);
    static void warning(std::string message);
    static void error(std::string message);

    static void log(const std::string &message, int level);

    static const int Debug = 4;
    static const int Message = 3;
    static const int Warning = 2;
    static const int Error = 1;
};
