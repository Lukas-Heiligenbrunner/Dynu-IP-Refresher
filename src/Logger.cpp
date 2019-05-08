//
// Created by lukas on 05.05.19.
//

#include <fstream>
#include <ctime>
#include <iostream>
#include <sstream>

#include "Logger.h"

void Logger::safeip(std::string ip) {
    std::ofstream out;
    out.open("ip.txt", std::ios::out);

    out << ip;

    out.close();
}

std::string Logger::readip() {
    std::ifstream in;
    in.open("ip.txt", std::ios::in);

    std::string ip;

    in >> ip;

    return ip;
}

void Logger::logToLogfile(std::string text) {
    std::ofstream out;
    out.open("dynurefresher.log", std::ios::out | std::ios::app);


    std::time_t t = std::time(0);   // get time now
    std::tm *now = std::localtime(&t);

    std::stringstream logline;

    logline << "[ " << (now->tm_year + 1900) << '-' << (now->tm_mon + 1) << '-' << now->tm_mday
            << "_" << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec << " ] " << '\t' << text << std::endl;


    out << logline.str();

    out.close();
}
