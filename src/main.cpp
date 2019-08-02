#include <iostream>
#include <IPRefresher.h>

int main(int argc, char *argv[]) {

    if (argc > 1) {
        std::string firstarg(argv[1]);
        if (firstarg == "-h" || firstarg == "--help") {
            std::cout << "help page: " << std::endl << "[-h] [--help]  print this help page" << std::endl
                      << "[-v] [--version] print the software version" << std::endl
                      << "[no argument] normal ip check and refresh" << std::endl;
        } else if (firstarg == "-v" || firstarg == "--version") {
            std::cout << "Version 1.0" << std::endl;
        } else {
            std::cout << "wrong arguments!  -h for help" << std::endl;
        }
    } else {
        IPRefresher ipr;
        ipr.checkIPAdress();
    }

    return 0;
}