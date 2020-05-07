//
// Created by lukas on 07.05.20.
//

#pragma once

#include <string>

/**
 * General helper class for IP actions
 */
class IpHelper {
public:
    /**
     * check if ip is valid
     * @param ip ip address to test
     * @return validity
     */
    static bool isIpValid(std::string ip);

private:
};
