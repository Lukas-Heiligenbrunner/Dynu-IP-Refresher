//
// Created by lukas on 18.06.19.
//

#pragma once

#include <string>
#include "API.h"

class IPAPI : API{
public:
    /**
     * get global ip of current internet connection
     * @return  global ip
     */
    std::string getGlobalIp();
};
