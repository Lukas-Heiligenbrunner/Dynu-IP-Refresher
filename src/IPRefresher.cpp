//
// Created by lukas on 02.08.19.
//

#include "IPRefresher.h"
#include "FileLogger.h"
#include "api/IPAPI.h"
#include "api/DynuAPI.h"
#include "api/TelegramAPI.h"
#include "Config.h"
#include "Version.h"

#include <string>
#include <chrono>
#include <thread>
#include <Logger.h>
#include <climits>

void IPRefresher::checkIPAdress(bool force) {
    FileLogger logger;

    IPAPI ipapi;
    std::string ip = ipapi.getGlobalIp();

    if (ip.empty()) {
        //no internet connection (or other error)
        Logger::warning("no internet connection");
    } else if (ip.find(':') == ULONG_MAX) {
        // error when ip doesn't contain a :
        Logger::warning("an error occured when getting the global ip");
    } else {
        std::string oldip = logger.readip();

        if (oldip == ip && !force) {
            Logger::message("no change -- ip: " + ip);
        } else {
            Logger::message("ip changed! -- from :" + oldip + "to: " + ip);

            DynuAPI dynu;
            dynu.init(Config::dynuapikey, Config::domainid, Config::domainname);

            if (dynu.refreshIp(ip)) {
                TelegramAPI tele;
                tele.init(Config::telegramApiKey, Config::chatId);
                tele.sendMessage(oldip + " moved to " + ip);
            } else {
                //error
                Logger::error("failed to write ip to dynu api!");
            }

            logger.safeip(ip);
        }
    }
}

IPRefresher::IPRefresher() = default;

IPRefresher::IPRefresher(bool loop) {
    if (loop) {
        Logger::message("startup of service");
        Logger::message("Version: " + Version::VERSION);
        if (Config::readCredentials()) {
            while (true) {
                Logger::message("starting check");
                checkIPAdress(false);
                std::this_thread::sleep_for(std::chrono::milliseconds(300000));
            }
        } else {
            std::cout << "incorrect credentials!" << std::endl;
        }
    }
}
