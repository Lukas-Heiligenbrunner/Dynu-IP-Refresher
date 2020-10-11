/**
 * A static class to manage the configuration file, read/write parameters to it.
 *
 * @author Lukas Heiligenbrunner
 * @date 11.02.2020
 */

#pragma once

#include <string>

class Config {
public:
    /**
    * read configuration out of config file
    *
    * @return success of config read
    */
    static bool readConfig();

    /**
     * save back configuration to file
     *
     * @return success of config write
     */
    static bool saveConfig();

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

    /**
     * set all parameters without telegram support
     *
     * @param domainname Dynu Domain name
     * @param dynuapikey Dynu api key
     * @param domainid Dynu domain id
     */
    static void setValues(const std::string &domainname, const std::string &dynuapikey, const std::string &domainid);

    /**
     * set all parameters with telegram support
     *
     * @param domainname Dynu Domain name
     * @param dynuapikey Dynu api key
     * @param domainid Dynu domain id
     * @param telegramApiKey Telegram api key
     * @param chatId Telegram chat id
     */
    static void setValues(const std::string &domainname, const std::string &dynuapikey, const std::string &domainid,
                          const std::string &telegramApiKey, const std::string &chatId);

private:
    /**
     * private constructor --> don't allow instance of this class
     */
    Config() = default;

    /**
     * helper variable for managing telegram Support
     */
    static bool telegramSupport;

    /**
     * helper variables for storing keys and ids
     */
    static std::string dynuapikey;
    static std::string domainid; //id of the dynu domain
    static std::string domainname;
    static std::string telegramApiKey;
    static std::string chatId;
};