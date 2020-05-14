#include "IPRefresher.h"
#include "FileLogger.h"
#include "api/IPAPI.h"
#include "api/DynuAPI.h"
#include "api/TelegramAPI.h"
#include "Config.h"
#include "Version.h"
#include "IpHelper.h"

#include <chrono>
#include <thread>
#include <Logger.h>

bool IPRefresher::checkIPAdress(bool force) {
    FileLogger logger;
    testspace::testi5();
    IPAPI ipapi;
    std::string ip = ipapi.getGlobalIp();

    if (ip.empty()) {
        //no internet connection (or other error)
        Logger::warning("no internet connection");
        return IPRefresher_Status_Code::ERROR_NO_INTERNET;
    } else if (!IpHelper::isIpValid(ip)) {
        // error when ip doesn't contain a :
        Logger::warning("an error occured when getting the global ip");
        return IPRefresher_Status_Code::ERROR;
    } else {
        std::string oldip = logger.readip();

        if (oldip == ip && !force) {
            Logger::message("no change -- ip: " + ip);
            return IPRefresher_Status_Code::NOREFRESH;
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
                return IPRefresher_Status_Code::ERROR;
            }

            logger.safeip(ip);
            return result ? IPRefresher_Status_Code::SUCCESS : IPRefresher_Status_Code::ERROR;
        }
    }
}

IPRefresher::IPRefresher(bool loop) {
    if (loop) {
        Logger::message("startup of service");
        Logger::message("Version: " + Version::VERSION);
        if (Config::readConfig()) {
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
