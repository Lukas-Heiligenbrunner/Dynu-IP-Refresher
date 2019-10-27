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

void IPRefresher::checkIPAdress(bool force) {
    FileLogger logger;

    IPAPI ipapi;
    std::string ip = ipapi.getGlobalIp();

    if (ip.empty()) {
        //no internet connection
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

            if (dynu.refreshIp(ip)) {
                TelegramAPI tele;
                tele.init("717213769:AAHan1nSXhUsxLJAN1Dv8Oc0z8wqwDdYPn4", "618154204");
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

}

IPRefresher::IPRefresher(bool loop) {
    Logger::message("startup of service");
    while (loop) {
        Logger::message("starting check");
        checkIPAdress(false);
        std::this_thread::sleep_for(std::chrono::milliseconds(300000));
    }
}
