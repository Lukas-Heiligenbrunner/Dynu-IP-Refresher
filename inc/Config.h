//
// Created by lukas on 11.02.20.
//

#pragma once

#include <string>

class Config {
public:
    static std::string dynuapikey;

    static std::string domainid; //id of the dynu domain
    static std::string domainname;

    static std::string telegramApiKey;
    static std::string chatId;

    /**
     * read configuration out of config file
     *
     * @return success of config read
     */
    static bool readCredentials();

    /**
     * validate config file
     *
     * @return validity of config file
     */
    static bool validateConfig();

private:
};