/**
 * Dynu API - Refresh the IP
 *
 * @author Lukas Heiligenbrunner
 * @date 18.06.2019
 */

#pragma once

#include "API.h"

class DynuAPI : API {
public:
    /**
     * refresh the ip of domain on Dynu server
     * @param ip new ip
     * @return request status
     */
    bool refreshIp(std::string ip);

    /**
     * init Telegram api with apikey and chatid
     * @param dynuApiKey Dynu Api key
     * @param domainId ID of domain received by Dynu
     * @param domainName domainname to refresh
     */
    void init(const std::string &dynuApiKey, const std::string &domainId, const std::string &domainName);

private:
    /**
     * Dynu API Key
     */
    std::string dynuapikey;

    /**
     * Dynu Domain ID
     */
    std::string domainid;

    /**
     * Domain name eg. "mydomain.dynu.net"
     */
    std::string domainname;
};
