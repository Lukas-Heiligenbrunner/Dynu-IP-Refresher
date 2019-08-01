//
// Created by lukas on 18.06.19.
//

#pragma once


#include "API.h"

class DynuAPI : API{
public:
    /**
     * refresh the ip of domain on Dynu server
     * @param ip new ip
     * @return request status
     */
    int refreshIp(std::string ip);
private:
    const std::string dynuapikey = "88vNpMfDhMM2YYDNfWR1DNYfRX9W6fYg";

    const std::string domainid = "8506047"; //id of the dynu domain
    const std::string domainname = "luki.dynu.net";
};
