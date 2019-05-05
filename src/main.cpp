#include <iostream>
#include <ctime>
#include "API.h"
#include "Logger.h"

int main() {
    API api;
    Logger logger;


    std::string ip = api.request("https://api.ipify.org");
    std::cout << "ip is: " << ip <<std::endl;

    std::string oldip = logger.readip();

    if(oldip == ip){
        std::cout << "no change -- ip: " << ip << std::endl;
        logger.logToLogfile("no change -- ip: "+ip);
    } else{
        logger.logToLogfile("ip changed! -- from :" + oldip + "to: "+ip);
        std::cout << "ip changed! -- from :" << oldip << "to: " << ip << std::endl;

        //api key: 88vNpMfDhMM2YYDNfWR1DNYfRX9W6fYg

        Hashmap<std::string, std::string> args;

        args.add("name","luki.dynu.net");
        args.add("ipv4Address",ip);

        std::vector<std::string> headers;
        headers.push_back("accept: application/json");
        headers.push_back("User-Agent: Mozilla/5.0 (compatible; Rigor/1.0.0; http://rigor.com)");
        headers.push_back("API-Key: 88vNpMfDhMM2YYDNfWR1DNYfRX9W6fYg");

        std::string dynurepl = api.request("https://api.dynu.com/v2/dns/8506047",true, args,headers);

        std::cout << "---" << dynurepl << std::endl;

        logger.safeip(ip);
    }



    return 0;
}