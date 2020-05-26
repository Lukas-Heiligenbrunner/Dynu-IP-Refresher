#include "api/TelegramAPI.h"
#include "Logger.h"

int TelegramAPI::sendMessage(const std::string &text) {
    Hashmap<std::string, std::string> args;
    args.add("chat_id", chatid);
    args.add("text", text);

    std::vector<std::string> headers;

    std::string reply = request("https://api.telegram.org/bot" + apikey + "/sendmessage", false, args, headers);

    if (reply.find("\"error_code\"") != SIZE_MAX) {
        Logger::error("failed to send the Telegram Message");
        return -1;
    }
    return 1;
}

void TelegramAPI::init(const std::string apikey, const std::string chatid) {
    this->apikey = apikey;
    this->chatid = chatid;
}
