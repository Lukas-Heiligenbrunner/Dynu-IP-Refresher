//
// Created by lukas on 18.06.19.
//

#include "api/DynuAPI.h"

int DynuAPI::refreshIp(std:: string ip) {
    Hashmap<std::string, std::string> args;
    args.add("name", domainname);
    args.add("ipv4Address", ip);

    std::vector<std::string> headers;
    headers.emplace_back("accept: application/json");
    headers.emplace_back("User-Agent: Mozilla/5.0 (compatible; Rigor/1.0.0; http://rigor.com)");
    headers.emplace_back("API-Key: " + dynuapikey);

    const std::string dynurepl = request("https://api.dynu.com/v2/dns/" + domainid, true, args, headers);

    if (dynurepl != "{\"statusCode\":200}") {
        return -1;
    } else {
        return 1;
    }
}

void DynuAPI::init(const std::string& dynuApiKey, const std::string& domainId, const std::string& domainName) {
    this->dynuapikey=dynuApiKey;
    this->domainid=domainId;
    this->domainname=domainName;
}
