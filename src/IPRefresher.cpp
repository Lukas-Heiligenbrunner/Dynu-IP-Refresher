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

#include <IPRefresher.h>

void IPRefresher::checkIPAdress(bool force) {
    FileLogger logger;

    IPAPI ipapi;
    std::string ip = ipapi.getGlobalIp();

    if (ip.empty()) {
        //no internet connection
        logger.logToLogfile("[WARNING] no internet connection");
        std::cout << "[WARNING] no internet connection" << std::endl;
    } else {
        std::string oldip = logger.readip();

    if (oldip == ip && !force) {
            std::cout << "[INFO] no change -- ip: " << ip << std::endl;
            logger.logToLogfile(" [INFO] no change -- ip: " + ip);
        } else {
            logger.logToLogfile(" [INFO] ip changed! -- from :" + oldip + "to: " + ip);
            std::cout << "[INFO] ip changed! -- from :" << oldip << "to: " << ip << std::endl;

            DynuAPI dynu;

            if (dynu.refreshIp(ip)) {
                TelegramAPI tele;
                tele.init("717213769:AAHan1nSXhUsxLJAN1Dv8Oc0z8wqwDdYPn4","618154204");
                tele.sendMessage(oldip + " moved to " + ip);
            } else {
                //error
                logger.logToLogfile(" [ERROR] failed to write ip to dynu api!");
            }

            logger.safeip(ip);
        }
    }
}

IPRefresher::IPRefresher() {

}

IPRefresher::IPRefresher(bool loop) {
    std::cout << "[INFO] startup of service" << std::endl;
    while(true){
        std::cout << "[INFO] starting check" << std::endl;
        checkIPAdress(false);
        std::this_thread::sleep_for(std::chrono::milliseconds(300000));
    }
}
