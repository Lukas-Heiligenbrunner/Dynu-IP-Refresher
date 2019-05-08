#include <iostream>
#include <ctime>

#include "api/API.h"
#include "Logger.h"
#include "api/TelegramAPI.h"

int main(int argc, char *argv[]) {

    if (argc > 1) {
        std::string firstarg(argv[1]);
        if (firstarg == "-h" || firstarg == "--help") {
            std::cout << "help page: " << std::endl << "[-h] [--help]  print this help page" << std::endl
                      << "[-v] [--version] print the software version" << std::endl
                      << "[no argument] normal ip check and refresh" << std::endl;
        } else if (firstarg == "-v" || firstarg == "--version") {
            std::cout << "Version 1.0" << std::endl;
        } else {
            std::cout << "wrong arguments!  -h for help" << std::endl;
        }
    } else {
        API api;
        Logger logger;

        std::string ip = api.request("https://api.ipify.org");

        if (ip == "") {
            //no internet connection
            logger.logToLogfile("[WARNING] no internet connection");
            std::cout << "[WARNING] no internet connection" << std::endl;
        } else {
            std::string oldip = logger.readip();

            if (oldip == ip) {
                std::cout << "[INFO] no change -- ip: " << ip << std::endl;
                logger.logToLogfile(" [INFO] no change -- ip: " + ip);
            } else {
                logger.logToLogfile(" [INFO] ip changed! -- from :" + oldip + "to: " + ip);
                std::cout << "[INFO] ip changed! -- from :" << oldip << "to: " << ip << std::endl;

                static std::string dynuapikey = "88vNpMfDhMM2YYDNfWR1DNYfRX9W6fYg";

                static std::string domainid = "8506047"; //id of the dynu domain
                static std::string domainname = "luki.dynu.net";

                Hashmap<std::string, std::string> args;
                args.add("name", domainname);
                args.add("ipv4Address", ip);

                std::vector<std::string> headers;
                headers.push_back("accept: application/json");
                headers.push_back("User-Agent: Mozilla/5.0 (compatible; Rigor/1.0.0; http://rigor.com)");
                headers.push_back("API-Key: " + dynuapikey);

                std::string dynurepl = api.request("https://api.dynu.com/v2/dns/" + domainid, true, args, headers);

                std::cout << "[DEBUG] api reply:: " << dynurepl << std::endl;

                if (dynurepl != "{\"statusCode\":200}") {
                    logger.logToLogfile(" [ERROR] failed to write ip to dynu api!");
                } else {
                    TelegramAPI tele;
                    tele.sendMessage(oldip + " moved to " + ip);
                }

                logger.safeip(ip);
            }
        }
    }

    return 0;
}