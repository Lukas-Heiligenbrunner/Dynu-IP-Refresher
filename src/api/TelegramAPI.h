//
// Created by lukas on 08.05.19.
//

#ifndef IPREFRESHER_TELEGRAMAPI_H
#define IPREFRESHER_TELEGRAMAPI_H


#include <string>
#include "API.h"

class TelegramAPI : API {
public:
    void sendMessage(std::string text);

private:
    std::string apikey = "717213769:AAHan1nSXhUsxLJAN1Dv8Oc0z8wqwDdYPn4";
    std::string chatid = "618154204";
};


#endif //IPREFRESHER_TELEGRAMAPI_H
