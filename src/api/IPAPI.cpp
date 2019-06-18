//
// Created by lukas on 18.06.19.
//

#include "IPAPI.h"

std::string IPAPI::getGlobalIp() {
    return request("https://api.ipify.org");
}
