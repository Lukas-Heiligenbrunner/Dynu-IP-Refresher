//
// Created by lukas on 11.02.20.
//

#include <Credentials.h>

std::string Credentials::dynuapikey = "";
std::string Credentials::domainid = ""; //id of the dynu domain
std::string Credentials::domainname = "";

std::string Credentials::telegramApiKey = "";
std::string Credentials::chatId = "";

bool Credentials::checkCredentialValidity() {
    return !(Credentials::dynuapikey.empty() || Credentials::domainid.empty() || Credentials::domainname.empty());
}
