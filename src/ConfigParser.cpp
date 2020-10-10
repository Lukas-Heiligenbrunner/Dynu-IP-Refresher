//
// Created by lukas on 09.10.20.
//

#include <string>
#include <inc/StaticData.h>
#include <fstream>
#include <regex>
#include <iostream>
#include "inc/ConfigParser.h"

bool ConfigParser::loadConfig() {
    const std::string config = StaticData::ConfigDir + StaticData::ConfName;

    const std::regex matchcomment(R"(^\s*#)"); // match hash to be a comment line
    const std::regex matchkey(R"(.+(?=\=.+))");
    const std::regex matchvalue(R"((?:=(.+)(?=\s*#*)))");

    std::map<std::string, std::string> entries;

    std::ifstream myfile(config);
    if (myfile.is_open()) {
        std::string line;

        while (getline(myfile, line)) {
            if (std::regex_search(line, matchcomment) || line == "") {
                // comment line
                continue;
            }

            // parse a key value pair
            std::smatch mk, mv;
            std::regex_search(line, mk, matchkey);
            std::regex_search(line, mv, matchvalue);

            if (!mk.empty() && !mv.empty()){
                entries.insert(std::pair<std::string, std::string>(mk[0], mv[0]));
                std::cout << mk[0] << "--" << mv[0] << std::endl;
            }


        }
        myfile.close();
    } else return false;

    return true;
}

bool ConfigParser::saveConfig() {
    // todo
    return false;
}

bool ConfigParser::validateConfig() {
    // todo
    return false;
}

bool ConfigParser::isTelegramSupported() {
    return false;
}

const std::string &ConfigParser::getDynuapikey() {
    return "";
}

const std::string &ConfigParser::getDomainid() {
    return "";
}

const std::string &ConfigParser::getDomainname() {
    return "";
}

const std::string &ConfigParser::getTelegramApiKey() {
    return "";
}

const std::string &ConfigParser::getChatId() {
    return "";
}
