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

    /**
     * init Telegram api with apikey and chatid
     * @param dynuApiKey Dynu Api key
     * @param domainId ID of domain received by Dynu
     * @param domainName domainname to refresh
     */
    void init(const std::string& dynuApiKey, const std::string& domainId, const std::string& domainName);
private:
    std::string dynuapikey; // Dynu API key

    std::string domainid; //id of the dynu domain
    std::string domainname;
};
