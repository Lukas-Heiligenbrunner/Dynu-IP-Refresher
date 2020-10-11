#include <regex>
#include "IpHelper.h"

bool IpHelper::isIpValid(const std::string& ip) {
    const std::regex rgx(R"(^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}$)");
    return (std::regex_match(ip, rgx));
}
