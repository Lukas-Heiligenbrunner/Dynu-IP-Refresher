/**
 * Read and write current ip to a temp file to remember last ip until restart
 *
 * @author Lukas Heiligenbrunner
 * @date 05.05.2019
 */

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
