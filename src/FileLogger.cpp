//
// Created by lukas on 05.05.19.
//

#include <fstream>
#include <iostream>
#include <climits>

#include "FileLogger.h"

void FileLogger::safeip(std::string ip) {
    std::ofstream out;
    out.open("ip.txt", std::ios::out);

    out << ip;

    out.close();
}

std::string FileLogger::readip() {
    std::ifstream in;
    in.open("ip.txt", std::ios::in);

    std::string ip;

    in >> ip;

    // when received ip has no : return 0.0.0.0
    if (ip.find(':') == ULONG_MAX)
        return "0.0.0.0";
    else
        return ip;
}
