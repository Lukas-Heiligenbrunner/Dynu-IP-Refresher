//
// Created by lukas on 18.06.19.
//

#ifndef IPREFRESHER_IPAPI_H
#define IPREFRESHER_IPAPI_H


#include <string>
#include "API.h"

class IPAPI : API{
public:
    std::string getGlobalIp();

};


#endif //IPREFRESHER_IPAPI_H
