/**
 * Telegram API for sending message to specific chat
 *
 * @author Lukas Heiligenbrunner
 * @date 08.05.2019
 */

#pragma once

#include "API.h"

#include <string>

class TelegramAPI : API {
public:
    /**
     * send telegram Message to predefined destination
     * @param text message
     */
    int sendMessage(const std::string &text);

    /**
     * init Telegram api with apikey and chatid
     * @param apikey recieved API key
     * @param chatid chatid where bot should post into
     */
    void init(std::string apikey, std::string chatid);

private:
    std::string apikey;
    std::string chatid;
};
