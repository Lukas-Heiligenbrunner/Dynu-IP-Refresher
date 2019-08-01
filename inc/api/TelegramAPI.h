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

private:
    const std::string apikey = "717213769:AAHan1nSXhUsxLJAN1Dv8Oc0z8wqwDdYPn4";
    const std::string chatid = "618154204";
};
