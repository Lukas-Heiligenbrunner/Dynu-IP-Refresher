//
// Created by lukas on 08.05.19.
//

#include "api/TelegramAPI.h"

void TelegramAPI::sendMessage(std::string text) {
    Hashmap<std::string, std::string> args;
    args.add("chat_id", chatid);
    args.add("text", text);

    std::vector<std::string> headers;

    std::string reply = request("https://api.telegram.org/bot" + apikey + "/sendmessage", false, args, headers);
//    std::cout << "[DEBUG] " << reply << std::endl;
}
