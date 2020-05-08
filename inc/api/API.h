/**
 * API class
 * - manages all curl download stuff
 * - easy POST/GET requests
 *
 * @author Lukas Heiligenbrunner
 * @date 06.04.2019
 */

#pragma once

#include "Hashmap.h"

#include <string>

class API {
public:
    /**
     * Simple API get request
     * @param myurl api url
     * @return return string of server
     */
    std::string request(std::string myurl);

    /**
     * complex request with post/get and header information support
     * @param myurl base request url
     * @param post boolean (false=get)
     * @param map post/get fields
     * @param headers header fields
     * @return return string of server
     */
    std::string request(std::string myurl,
                        bool post,
                        Hashmap<std::string, std::string> &map,
                        std::vector<std::string> &headers);

private:
    static size_t write_data(void *buffer, size_t size, size_t buffersize, FILE *stream);
};
