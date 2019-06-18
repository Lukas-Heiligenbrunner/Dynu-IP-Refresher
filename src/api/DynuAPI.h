//
// Created by lukas on 18.06.19.
//

#ifndef IPREFRESHER_DYNUAPI_H
#define IPREFRESHER_DYNUAPI_H


#include "API.h"

class DynuAPI : API{
public:
    int refreshIp(std::string ip);
private:
    const std::string dynuapikey = "88vNpMfDhMM2YYDNfWR1DNYfRX9W6fYg";

    const std::string domainid = "8506047"; //id of the dynu domain
    const std::string domainname = "luki.dynu.net";
};


#endif //IPREFRESHER_DYNUAPI_H
