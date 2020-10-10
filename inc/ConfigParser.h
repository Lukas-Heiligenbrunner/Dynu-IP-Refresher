//
// Created by lukas on 09.10.20.
//

#pragma once


class ConfigParser {
public:
    static bool loadConfig();
    bool saveConfig();
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
};
