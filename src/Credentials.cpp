//
// Created by lukas on 11.02.20.
//

#include <Credentials.h>
#include <iostream>
#include <cstring>

#include "libconfig.h++"

std::string Credentials::dynuapikey;
std::string Credentials::domainid; //id of the dynu domain
std::string Credentials::domainname;

std::string Credentials::telegramApiKey;
std::string Credentials::chatId;

bool Credentials::readCredentials() {
    libconfig::Config cfg;
    try {
        cfg.readFile("/etc/iprefresher.cfg");
    }
    catch (const libconfig::FileIOException &fioex) {
        std::cout << "I/O error while reading config file." << std::endl << "creating new config file!" << std::endl;
        cfg.writeFile("/etc/iprefresher.cfg");
        return false;
    }
    catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return false;
    }

    // Get the store name.
    try {
        // needed parameters
        dynuapikey = (std::string) cfg.lookup("dynuapikey");
        domainid = (std::string) cfg.lookup("domainid");
        domainname = (std::string) cfg.lookup("domainname");
        // optional parameters
        telegramApiKey = (std::string) cfg.lookup("telegramApiKey");
        chatId = (std::string) cfg.lookup("chatId");
        std::cout << "Store name: " << dynuapikey << std::endl;
    }
    catch (const libconfig::SettingNotFoundException &nfex) {
        // triggered if setting is missing in config
        if (!(std::strcmp("telegramApiKey", nfex.getPath()) == 0 || std::strcmp("chatId", nfex.getPath()) == 0)) {
            std::cerr << "No '" << nfex.getPath() << "' setting in configuration file." << std::endl;
        }
    }
    return !(Credentials::dynuapikey.empty() || Credentials::domainid.empty() || Credentials::domainname.empty());
}
