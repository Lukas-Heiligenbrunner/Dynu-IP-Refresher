#include "IpHelper.h"

bool IpHelper::isIpValid(std::string ip) {
    return (ip.find('.') != SIZE_MAX);
}
