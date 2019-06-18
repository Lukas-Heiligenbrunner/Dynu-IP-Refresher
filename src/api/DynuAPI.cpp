//
// Created by lukas on 18.06.19.
//

#include "DynuAPI.h"

int DynuAPI::refreshIp(std:: string ip) {

    static std::string dynuapikey = "88vNpMfDhMM2YYDNfWR1DNYfRX9W6fYg";

    static std::string domainid = "8506047"; //id of the dynu domain
    static std::string domainname = "luki.dynu.net";

    Hashmap<std::string, std::string> args;
    args.add("name", domainname);
    args.add("ipv4Address", ip);

    std::vector<std::string> headers;
    headers.push_back("accept: application/json");
    headers.push_back("User-Agent: Mozilla/5.0 (compatible; Rigor/1.0.0; http://rigor.com)");
    headers.push_back("API-Key: " + dynuapikey);

    std::string dynurepl = request("https://api.dynu.com/v2/dns/" + domainid, true, args, headers);

    std::cout << "[DEBUG] api reply:: " << dynurepl << std::endl;

    if (dynurepl != "{\"statusCode\":200}") {
        return -1;
    } else {
        return 1;
    }
}
