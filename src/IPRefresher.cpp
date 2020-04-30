//
// Created by lukas on 02.08.19.
//

#include <string>

#include <FileLogger.h>
#include <api/IPAPI.h>
#include <api/DynuAPI.h>
#include <api/TelegramAPI.h>

#include <chrono>
#include <thread>
#include <Logger.h>

#include <IPRefresher.h>
#include <Credentials.h>

void IPRefresher::checkIPAdress(bool force) {
    FileLogger logger;

    IPAPI ipapi;
    std::string ip = ipapi.getGlobalIp();

    if (ip.empty()) {
        //no internet connection (or other error)
        logger.logToLogfile("[WARNING] no internet connection");
        Logger::warning("no internet connection");
    } else {
        std::string oldip = logger.readip();

        if (oldip == ip && !force) {
            Logger::message("no change -- ip: " + ip);
            logger.logToLogfile(" [INFO] no change -- ip: " + ip);
        } else {
            logger.logToLogfile(" [INFO] ip changed! -- from :" + oldip + "to: " + ip);
            Logger::message("ip changed! -- from :" + oldip + "to: " + ip);

            DynuAPI dynu;
            dynu.init(Credentials::dynuapikey, Credentials::domainid, Credentials::domainname);

            if (dynu.refreshIp(ip)) {
                TelegramAPI tele;
                tele.init(Credentials::telegramApiKey, Credentials::chatId);
                tele.sendMessage(oldip + " moved to " + ip);
            } else {
                //error
                logger.logToLogfile(" [ERROR] failed to write ip to dynu api!");
                Logger::error("failed to write ip to dynu api!");
            }

            logger.safeip(ip);
        }
    }
}

IPRefresher::IPRefresher() {
    // default constructor
}

IPRefresher::IPRefresher(bool loop) {
    if (Credentials::readCredentials()) {
        Logger::message("startup of service");
        while (loop) {
            Logger::message("starting check");
            checkIPAdress(false);
            std::this_thread::sleep_for(std::chrono::milliseconds(300000));
        }
    } else {
        std::cout << "incorrect credentials!" << std::endl;
    }
}
