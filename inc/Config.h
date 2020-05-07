//
// Created by lukas on 11.02.20.
//

#pragma once

#include <string>

/**
 * A static class to manage the configuration file, read/write parameters to it.
 */
class Config {
public:
    /**
    * read configuration out of config file
    *
    * @return success of config read
    */
    static bool readConfig();

    /**
     * validate config file
     *
     * @return validity of config file
     */
    static bool validateConfig();

    /**
     * check if telegram credentials in config are set
     * @return is supported?
     */
    static bool isTelegramSupported();

    /** Getters **/

    /**
     * encapsulated getter for DynuApiKey
     * @return api key
     */
    static const std::string &getDynuapikey();

    /**
     * encapsulated getter for DomainId
     * @return DomainId
     */
    static const std::string &getDomainid();

    /**
     * encapsulated getter for Domainname
     * @return Domainname
     */
    static const std::string &getDomainname();

    /**
     * encapsulated getter for TelegramApiKey
     * @return TelegramApiKey
     */
    static const std::string &getTelegramApiKey();

    /**
     * encapsulated getter for ChatId
     * @return ChatId
     */
    static const std::string &getChatId();


private:
    /**
     * private constructor --> don't allow instance of this class
     */
    Config();

    /**
     * helper variable for managing telegram Support
     */
    static bool telegramSupport;

    static std::string dynuapikey;

    static std::string domainid; //id of the dynu domain
    static std::string domainname;

    static std::string telegramApiKey;
    static std::string chatId;
};