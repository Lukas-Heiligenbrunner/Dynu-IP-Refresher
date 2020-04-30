//
// Created by lukas on 08.05.19.
//

#include "api/TelegramAPI.h"

#include <Logger.h>

int TelegramAPI::sendMessage(const std::string& text) {
    Hashmap<std::string, std::string> args;
    args.add("chat_id", chatid);
    args.add("text", text);

    std::vector<std::string> headers;

    std::string reply = request("https://api.telegram.org/bot" + apikey + "/sendmessage", false, args, headers);

    unsigned const long ULONG_MAX = -1;
    if (reply.find("\"error_code\"") != ULONG_MAX) {
        Logger::error("failed to refresh the ip (Dynu API)");
        return -1;
    }
    return 1;
}

void TelegramAPI::init(const std::string apikey, const std::string chatid) {
    this->apikey = apikey;
    this->chatid = chatid;
}
