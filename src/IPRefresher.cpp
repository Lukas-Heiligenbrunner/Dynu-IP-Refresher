#include "IPRefresher.h"
#include "FileLogger.h"
#include "api/IPAPI.h"
#include "api/DynuAPI.h"
#include "api/TelegramAPI.h"
#include "Config.h"
#include "StaticData.h"
#include "IpHelper.h"

#include <chrono>
#include <thread>
#include <Logger.h>

void IPRefresher::checkIPAdress(bool force) {
    FileLogger logger;

    IPAPI ipapi;
    std::string ip = ipapi.getGlobalIp();

    if (ip.empty()) {
        //no internet connection (or other error)
        Logger::warning("no internet connection");
    } else if (!IpHelper::isIpValid(ip)) {
        // error when ip doesn't contain a :
        Logger::warning("an error occured when getting the global ip");
    } else {
        std::string oldip = logger.readip();

        if (oldip == ip && !force) {
            Logger::message("no change -- ip: " + ip);
        } else {
            Logger::message("ip changed! -- from :" + oldip + "to: " + ip);

            DynuAPI dynu;
            dynu.init(Config::getDynuapikey(), Config::getDomainid(), Config::getDomainname());
            // actual refresh of IP in api - here
            bool result = dynu.refreshIp(ip);

            if (result && Config::isTelegramSupported()) {
                TelegramAPI tele;
                tele.init(Config::getTelegramApiKey(), Config::getChatId());
                tele.sendMessage(oldip + " moved to " + ip);
            } else if (!result) {
                //error
                Logger::error("failed to write ip to dynu api!");
            }

            logger.safeip(ip);
        }
    }
}

IPRefresher::IPRefresher(bool loop) {
    if (loop) {
        Logger::message("startup of service");
        Logger::message("Version: " + StaticData::VERSION);

        while (true) {
            Logger::message("starting check");
            if (Config::readConfig()) {
                checkIPAdress(false);
            } else {
                std::cout << "incorrect credentials!" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(300000));
        }
    }
}
