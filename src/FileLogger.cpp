#include "FileLogger.h"
#include "IpHelper.h"
#include "StaticData.h"

#include <fstream>
#include <iostream>

void FileLogger::safeip(std::string ip) {
    std::ofstream out;
    out.open(StaticData::TempFilePath + "temp-dynuiprefresher.txt", std::ios::out);

    out << ip;

    out.close();
}

std::string FileLogger::readip() {
    std::ifstream in;
    in.open(StaticData::TempFilePath + "temp-dynuiprefresher.txt", std::ios::in);

    std::string ip;

    in >> ip;

    // when received ip has no . return 0.0.0.0
    if (!IpHelper::isIpValid(ip))
        return "0.0.0.0";
    else
        return ip;
}
