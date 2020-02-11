//
// Created by lukas on 11.02.20.
//

#pragma once


#include <string>

class Credentials {
public:
    static const std::string dynuapikey;

    static const std::string domainid; //id of the dynu domain
    static const std::string domainname;

    static const std::string telegramApiKey;
    static const std::string chatId;

    static bool checkCredentialValidity();
};

const std::string Credentials::dynuapikey = "";
const std::string Credentials::domainid = ""; //id of the dynu domain
const std::string Credentials::domainname = "";

static const std::string Credentials::telegramApiKey = "";
static const std::string Credentials::chatId = "";

bool Credentials::checkCredentialValidity() {
    return !(dynuapikey.empty() || domainid.empty() || domainname.empty());
}
