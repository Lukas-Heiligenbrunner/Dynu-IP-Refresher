//
// Created by lukas on 18.06.19.
//

#include <iostream>
#include <Version.h>
#include <IPRefresher.h>
#include <Logger.h>
#include <Config.h>

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
                      << "[no argument] normal ip check and refresh" << std::endl;
        } else if (firstarg == "-v" || firstarg == "--version") {
            std::cout << "Version " << Version::VERSION << std::endl;
        } else if (firstarg == "-f" || firstarg == "--force") {
            IPRefresher ipr;
            if (Config::readCredentials()) {
                ipr.checkIPAdress(true);
            } else {
                std::cout << "incorrect credentials!" << std::endl;
            }

        } else if (firstarg == "-l" || firstarg == "--loop") {
            IPRefresher(true);
        } else {
            Logger::message("wrong arguments!  -h for help");
        }
    } else {
        IPRefresher ipr;
        Logger::message("starting check");
        if (Config::readCredentials()) {
            ipr.checkIPAdress(false);
        } else {
            std::cout << "incorrect credentials!" << std::endl;
        }
    }

    return 0;
}