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

using namespace IPRefresher;

bool IPRefresher::checkIPAdress(bool force) {
    FileLogger logger;

    IPAPI ipapi;
    std::string ip = ipapi.getGlobalIp();

    if (ip.empty()) {
        //no internet connection (or other error)
        Logger::warning("no internet connection");
        return Status_Code::ERROR_NO_INTERNET;
    } else if (!IpHelper::isIpValid(ip)) {
        // error when ip doesn't contain a :
        Logger::warning("an error occured when getting the global ip");
        return Status_Code::ERROR;
    } else {
        std::string oldip = logger.readip();

        if (oldip == ip && !force) {
            Logger::message("no change -- ip: " + ip);
            return Status_Code::NOREFRESH;
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
                return Status_Code::ERROR;
            }

            logger.safeip(ip);
            return result ? Status_Code::SUCCESS : Status_Code::ERROR;
        }
    }
}

void IPRefresher::startUpService(int interval) {
    Logger::message("startup of service");
    Logger::message("Version: " + StaticData::VERSION);
    if (Config::readConfig()) {
        while (true) {
            Logger::message("starting check");
            if (Config::readConfig()) {
                checkIPAdress(false);
            } else {
                std::cout << "incorrect credentials!" << std::endl;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(interval * 1000));
        }
    } else {
        std::cout << "incorrect credentials!" << std::endl;
    }
}
