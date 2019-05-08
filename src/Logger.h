//
// Created by lukas on 05.05.19.
//

#ifndef IPREFRESHER_LOGGER_H
#define IPREFRESHER_LOGGER_H


class Logger {
public:
    void logToLogfile(std::string text);

    void safeip(std::string ip);

    std::string readip();

};


#endif //IPREFRESHER_LOGGER_H
