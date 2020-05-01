//
// Created by lukas on 11.02.20.
//

#include <Config.h>
#include <iostream>
#include <cstring>
#include <fstream>

#include "libconfig.h++"

std::string Config::dynuapikey;
std::string Config::domainid; //id of the dynu domain
std::string Config::domainname;

std::string Config::telegramApiKey;
std::string Config::chatId;

bool Config::readCredentials() {
    libconfig::Config cfg;
    try {
        cfg.readFile("/etc/iprefresher.cfg");
    }
    catch (const libconfig::FileIOException &fioex) {
        std::cout << "I/O error while reading config file." << std::endl << "creating new config file!" << std::endl;

        std::string defaultconf = R"(# Dynu IP refresher config
# 2020
# Lukas Heiligenbrunner

## DYNU API Config
dynuapikey = ""
domainid = ""
domainname = ""

## Telegram API Config (optional)
#telegramApiKey = ""
#chatId = ""
)";

        std::ofstream myfile;
        myfile.open("/etc/iprefresher.cfg");
        if(myfile.is_open()){
            myfile << defaultconf;
            myfile.close();
        } else {
            std::cout << "error creating file" << std::endl;
        }


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
    }
    catch (const libconfig::SettingNotFoundException &nfex) {
        // triggered if setting is missing in config
        if (!(std::strcmp("telegramApiKey", nfex.getPath()) == 0 || std::strcmp("chatId", nfex.getPath()) == 0)) {
            std::cerr << "No '" << nfex.getPath() << "' setting in configuration file." << std::endl;
        }
    }
    // check if needed values aren't empty
    return !(Config::dynuapikey.empty() || Config::domainid.empty() || Config::domainname.empty());
}
