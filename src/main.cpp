#include "Version.h"
#include "IPRefresher.h"
#include "Logger.h"
#include "Config.h"
#include "api/IPAPI.h"

/**
 * application entry point
 */
int main(int argc, char *argv[]) {
    if (argc > 1) {
        std::string firstarg(argv[1]);
        if (firstarg == "-h" || firstarg == "--help") {
            std::cout << "help page: " << std::endl << "[-h] [--help]  print this help page" << std::endl
                      << "[-v] [--version] print the software version" << std::endl
                      << "[-f] [--force] force refresh of ip" << std::endl
                      << "[-l] [--loop] infinite loop to refresh ip every five minutes" << std::endl
                      << "[-c] [--checkconfig] validate configuration" << std::endl
                      << "[-ip] [--currentip] get current global ip" << std::endl
                      << "[no argument] normal ip check and refresh" << std::endl;
        } else if (firstarg == "-v" || firstarg == "--version") {
            std::cout << "Version " << Version::VERSION << std::endl;
        } else if (firstarg == "-f" || firstarg == "--force") {
            if (Config::readConfig()) {
                IPRefresher::checkIPAdress(true);
            } else {
                std::cout << "incorrect credentials!" << std::endl;
            }

        } else if (firstarg == "-l" || firstarg == "--loop") {
            IPRefresher::startUpService(true);
        } else if (firstarg == "-c" || firstarg == "--checkconfig") {
            if (Config::validateConfig()) {
                Logger::message("Config file is OK");
            } else {
                Logger::error("There are errors in config file!");
                return -1;
            }
        } else if (firstarg == "-ip" || firstarg == "--currentip") {
            IPAPI ipapi;
            std::cout << "Current global IP: " << ipapi.getGlobalIp() << std::endl;
        } else {
            Logger::message("wrong arguments!  -h for help");
        }
    } else {
        Logger::message("starting check");
        if (Config::readConfig()) {
            IPRefresher::checkIPAdress(false);
        } else {
            std::cout << "incorrect credentials!" << std::endl;
        }
    }

    return 0;
}