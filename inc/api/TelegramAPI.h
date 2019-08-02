//
// Created by lukas on 08.05.19.
//

#pragma once


#include <string>
#include "API.h"

class TelegramAPI : API {
public:
    /**
     * send telegram Message to predefined destination
     * @param text message
     */
    void sendMessage(std::string text);

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
