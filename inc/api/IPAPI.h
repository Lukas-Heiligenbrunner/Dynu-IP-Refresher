/**
 * IPAPI for getting global ip of current network
 *
 * @author Lukas Heiligenbrunner
 * @date 18.06.2019
 */

#pragma once

#include "API.h"

#include <string>

class IPAPI : API {
public:
    /**
     * get global ip of current internet connection
     * @return  global ip
     */
    std::string getGlobalIp();
};
