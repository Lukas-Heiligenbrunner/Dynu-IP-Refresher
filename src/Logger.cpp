//
// Created by lukas on 26.10.19.
//

#include "Logger.h"

#include <sstream>
#include <iostream>

void Logger::debug(const std::string message) {
    log(message, Logger::Debug);
}

void Logger::message(const std::string message) {
    log(message, Logger::Message);
}

void Logger::warning(const std::string message) {
    log(message, Logger::Warning);
}

void Logger::error(const std::string message) {
    log(message, Logger::Error);
}

void Logger::log(const std::string &message, int level) {
    std::stringstream out;
    out << "[";
    switch (level) {
        case Debug:
            out << "DEBUG";
            break;
        case Message:
            out << "MESSAGE";
            break;
        case Warning:
            out << "WARNING";
            break;
        case Error:
            out << "ERROR";
            break;
        default:
            out << "UNDEFINED";
            break;
    }
    out << "] ";
    out << message;
    std::cout << out.str() << std::endl;
}

