#include "Config.h"
#include "Logger.h"
#include "StaticData.h"

#include <iostream>
#include <cstring>
#include <fstream>
#include <libconfig.h++>
#include <sys/stat.h>

std::string Config::dynuapikey;
std::string Config::domainid; //id of the dynu domain
std::string Config::domainname;

std::string Config::telegramApiKey;
std::string Config::chatId;

bool Config::telegramSupport;

bool Config::readConfig() {
    libconfig::Config cfg;
    try {
        cfg.readFile(std::string(StaticData::ConfigDir + StaticData::ConfName).c_str());
    }
    catch (const libconfig::FileIOException &fioex) {
        std::cout << "I/O error while reading config file." << std::endl << "creating new config file!" << std::endl;

        // check if config folder exists
        struct stat info{};

        if (stat(StaticData::ConfigDir.c_str(), &info) != 0) {
            Logger::warning("The config folder doesn't exist. Trying to create it.");

// mkdir command is different defined for windows
#ifdef __unix
            int check = mkdir(StaticData::ConfigDir.c_str(), 777);
#else
            int check = mkdir(StaticData::ConfigDir.c_str());
#endif

            // check if directory is created or not
            if (!check)
                Logger::message("config directory successfully created. ");
            else
                Logger::error("unable to create config directory.");

        } else if (info.st_mode & S_IFDIR) {
            Logger::debug("config directory exists already");
        } else {
            Logger::error("A file exists with the same name as the config dir should be");
        }


        std::ofstream myfile;
        myfile.open(StaticData::ConfigDir + StaticData::ConfName);
        if (myfile.is_open()) {
            myfile << StaticData::SAMPLECONFIG;
            myfile.close();
        } else {
            Logger::error("error creating file");
        }

        return false;
    }
    catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return false;
    }

    try {
        // needed parameters
        dynuapikey = (std::string) cfg.lookup("dynuapikey");
        domainid = (std::string) cfg.lookup("domainid");
        domainname = (std::string) cfg.lookup("domainname");
        // optional parameters
        telegramApiKey = (std::string) cfg.lookup("telegramApiKey");
        chatId = (std::string) cfg.lookup("chatId");
        telegramSupport = true;
    }
    catch (const libconfig::SettingNotFoundException &nfex) {
        // triggered if setting is missing in config
        if (!(std::strcmp("telegramApiKey", nfex.getPath()) == 0 || std::strcmp("chatId", nfex.getPath()) == 0)) {
            std::cerr << "No '" << nfex.getPath() << "' setting in configuration file." << std::endl;
        } else {
            Logger::message("no Telegram support - fields in config not set");
            telegramSupport = false;
        }
    }
    // check if needed values aren't empty
    return !(Config::dynuapikey.empty() || Config::domainid.empty() || Config::domainname.empty());
}

bool Config::saveConfig() {
    // todo save config
    return false;
}

bool Config::validateConfig() {
    libconfig::Config cfg;
    try {
        Logger::message("reading config file: " + std::string(StaticData::ConfigDir + StaticData::ConfName));
        cfg.readFile(std::string(StaticData::ConfigDir + StaticData::ConfName).c_str());
    }
    catch (const libconfig::FileIOException &fioex) {
        Logger::warning("config file doesn't exist or permission denied!");
        return false;
    }
    catch (const libconfig::ParseException &pex) {
        std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                  << " - " << pex.getError() << std::endl;
        return false;
    }
    Logger::message("Syntax and Permission is OK");

    try {
        // needed parameters
        if (((std::string) cfg.lookup("dynuapikey")).empty()) {
            Logger::warning("required parameter \"dynuapikey\" seems to be empty.");
            return false;
        }
        if (((std::string) cfg.lookup("domainid")).empty()) {
            Logger::warning("required parameter \"domainid\" seems to be empty.");
            return false;
        }
        if (((std::string) cfg.lookup("domainname")).empty()) {
            Logger::warning("required parameter \"domainname\" seems to be empty.");
            return false;
        }
        // optional parameters
        cfg.lookup("telegramApiKey");
        cfg.lookup("chatId");
        telegramSupport = true;
    }
    catch (const libconfig::SettingNotFoundException &nfex) {
        // triggered if setting is missing in config
        if (!(std::strcmp("telegramApiKey", nfex.getPath()) == 0 || std::strcmp("chatId", nfex.getPath()) == 0)) {
            std::cerr << "No '" << nfex.getPath() << "' setting in configuration file." << std::endl;
            return false;
        } else {
            Logger::message("no Telegram support - fields in config not set");
            telegramSupport = false;
        }
    }
    return true;
}

bool Config::isTelegramSupported() {
    return telegramSupport;
}

const std::string &Config::getDynuapikey() {
    return dynuapikey;
}

const std::string &Config::getDomainid() {
    return domainid;
}

const std::string &Config::getDomainname() {
    return domainname;
}

const std::string &Config::getTelegramApiKey() {
    return telegramApiKey;
}

const std::string &Config::getChatId() {
    return chatId;
}

void Config::setValues(const std::string &domainname, const std::string &dynuapikey, const std::string &domainid) {
    Config::domainname = domainname;
    Config::dynuapikey = dynuapikey;
    Config::domainid = domainid;
}

void Config::setValues(const std::string &domainname, const std::string &dynuapikey, const std::string &domainid, const std::string &telegramApiKey, const std::string &chatId) {
    setValues(domainname, dynuapikey, domainid);
    Config::telegramApiKey = telegramApiKey;
    Config::chatId = chatId;
}
