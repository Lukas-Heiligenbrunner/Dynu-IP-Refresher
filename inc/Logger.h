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

    static void log(std::string &message, int level);

    static const int Debug;
    static const int Message;
    static const int Warning;
    static const int Error;
};
