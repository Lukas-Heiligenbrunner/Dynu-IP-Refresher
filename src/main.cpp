#include <iostream>
#include <IPRefresher.h>
#include <Version.h>
#include <Logger.h>

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
            ipr.checkIPAdress(true);
        } else if (firstarg == "-l" || firstarg == "--loop") {
            IPRefresher ipr(true);
        } else {
            Logger::message("wrong arguments!  -h for help");
        }
    } else {
        IPRefresher ipr;
        Logger::message("starting check");
        ipr.checkIPAdress(false);

    }

    return 0;
}