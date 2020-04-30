//
// Created by lukas on 05.05.19.
//

#pragma once

#include <string>

class FileLogger {
public:
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
