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

    static bool readCredentials();

private:
};