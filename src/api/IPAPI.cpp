#include <inc/IpHelper.h>
#include <inc/Logger.h>
#include "api/IPAPI.h"

std::string IPAPI::getGlobalIp() {
    const std::string ip = request("https://api.ipify.org");
    if(!IpHelper::isIpValid(ip))
        Logger::warning("no valid ip returned from ipapi");

    return ip;
}