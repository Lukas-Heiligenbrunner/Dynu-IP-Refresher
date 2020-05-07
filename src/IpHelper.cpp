//
// Created by lukas on 07.05.20.
//

#include "IpHelper.h"

#include <climits>

bool IpHelper::isIpValid(std::string ip) {
    return (ip.find('.') != ULONG_MAX);
}
