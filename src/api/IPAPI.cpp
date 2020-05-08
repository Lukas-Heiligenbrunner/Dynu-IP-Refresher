#include "api/IPAPI.h"

std::string IPAPI::getGlobalIp() {
    return request("https://api.ipify.org");
}