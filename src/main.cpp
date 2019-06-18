#include <iostream>
#include <ctime>
#include <unordered_map>

#include "api/API.h"
#include "Logger.h"
#include "api/TelegramAPI.h"
#include "api/DynuAPI.h"
#include "api/IPAPI.h"

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
        Logger logger;

        IPAPI ipapi;
        std::string ip = ipapi.getGlobalIp();

        if (ip.empty()) {
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

                DynuAPI dynu;
                TelegramAPI tele;

                if(dynu.refreshIp(ip)){
                    tele.sendMessage(oldip + " moved to " + ip);
                } else{
                    //error
                    logger.logToLogfile(" [ERROR] failed to write ip to dynu api!");
                }

                logger.safeip(ip);
            }
        }
    }

    return 0;
}