#include <iostream>
#include <ctime>

#include "API.h"
#include "Logger.h"

int main() {
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
            std::cout << "no change -- ip: " << ip << std::endl;
            logger.logToLogfile(" [INFO] no change -- ip: " + ip);
        } else {
            logger.logToLogfile(" [INFO] ip changed! -- from :" + oldip + "to: " + ip);
            std::cout << "ip changed! -- from :" << oldip << "to: " << ip << std::endl;

            //dynu api key: 88vNpMfDhMM2YYDNfWR1DNYfRX9W6fYg

            static std::string domainid = "8506047"; //id of the dynu domain

            Hashmap<std::string, std::string> args;
            args.add("name", "luki.dynu.net");
            args.add("ipv4Address", ip);

            std::vector<std::string> headers;
            headers.push_back("accept: application/json");
            headers.push_back("User-Agent: Mozilla/5.0 (compatible; Rigor/1.0.0; http://rigor.com)");
            headers.push_back("API-Key: 88vNpMfDhMM2YYDNfWR1DNYfRX9W6fYg");

            std::string dynurepl = api.request("https://api.dynu.com/v2/dns/" + domainid, true, args, headers);

            std::cout << "[ DEBUG ] api reply:: " << dynurepl << std::endl;

            if (dynurepl != "{\"statusCode\":200}") {
                logger.logToLogfile(" [ERROR] failed to write ip to dynu api!");
            }

            logger.safeip(ip);
        }
    }

    return 0;
}