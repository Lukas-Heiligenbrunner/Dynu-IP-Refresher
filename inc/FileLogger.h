//
// Created by lukas on 05.05.19.
//
#pragma once

#include <string>
class FileLogger {
public:
    /**
     * log messages to logfile
     * @param text message
     */
    void logToLogfile(std::string text);

    /**
     * safe ip to temp file
     * @param ip ip address to save
     */
    void safeip(std::string ip);

    /**
     * read ip from file
     * @return read ip
     */
    std::string readip();

};
