//
// Created by lukas on 06.04.19.
//

#ifndef IPREFRESHER_API_H
#define IPREFRESHER_API_H


#include <string>
#include "../Hashmap.h"

class API {
public:
    std::string request(std::string myurl);
    std::string request(std::string myurl, bool post, Hashmap<std::string,std::string> &map,std::vector<std::string> &headers);

private:
    static size_t write_data(void *buffer, size_t size, size_t buffersize, FILE *stream);
};


#endif //IPREFRESHER_API_H
