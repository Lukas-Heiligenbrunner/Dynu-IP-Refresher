#include <iostream>
#include "API.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    API api;
    std::string mystr = api.request("https://api.ipify.org");
    std::cout << mystr <<std::endl;

    //88vNpMfDhMM2YYDNfWR1DNYfRX9W6fYg

    Hashmap<std::string, std::string> args;

    args.add("name","luki.dynu.net");
    args.add("group","office");
    args.add("ipv4Address","42.42.42.42");
    args.add("ipv6Address","42:42:42:42");
    args.add("ttl","90");
    args.add("ipv4","true");
    args.add("ipv6","true");
    args.add("ipv4WildcardAlias","true");
    args.add("ipv6WildcardAlias","true");
    args.add("allowZoneTrnsfer","false");
    args.add("dnssec","false");


    std::vector<std::string> headers;
    headers.push_back("API-Key: 88vNpMfDhMM2YYDNfWR1DNYfRX9W6fYg");
    std::string dynurepl = api.request("https://api.dynu.com/v2/dns/8506047",true, args,headers);

    std::cout << "---" << dynurepl << "\n";
/*
    "name": "somedomain.com",
            "group": "office",
            "ipv4Address": "1.2.3.4",
            "ipv6Address": "1111:2222:3333::4444",
            "ttl": 90,
            "ipv4": true,
            "ipv6": true,
            "ipv4WildcardAlias": true,
            "ipv6WildcardAlias": true,
            "allowZoneTransfer": false,
            "dnssec": false
            */


    return 0;
}