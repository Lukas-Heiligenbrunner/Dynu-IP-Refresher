#include "IpHelper.h"

#include <climits>

bool IpHelper::isIpValid(std::string ip) {
    return (ip.find('.') != ULONG_MAX);
}
