//
// Created by lukas on 26.10.19.
//

#include <sstream>
#include <iostream>

#include "Logger.h"


const int Logger::Warning = 1;
const int Logger::Debug = 2;
const int Logger::Message = 3;
const int Logger::Error = 4;

void Logger::debug(std::string message) {
    log(message, Logger::Debug);
}

void Logger::message(std::string message) {
    log(message, Logger::Message);
}

void Logger::warning(std::string message) {
    log(message, Logger::Warning);
}

void Logger::error(std::string message) {
    log(message, Logger::Error);
}

void Logger::log(std::string &message, int level) {
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
    }
    out << "] ";
    out << message;
    std::cout << out.str() << std::endl;
}

