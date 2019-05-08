//
// Created by lukas on 08.05.19.
//

#include "TelegramAPI.h"

void TelegramAPI::sendMessage(std::string text) {
    std::string reply = request("https://api.telegram.org/bot" + apikey + "/sendmessage?chat_id=" + chatid + "&text=" + text);
    std::cout << "[DEBUG] " << reply << std::endl;
}
