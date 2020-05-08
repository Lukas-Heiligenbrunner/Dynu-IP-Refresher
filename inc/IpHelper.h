/**
 * A helper class for general IP String actions
 *
 * @author Lukas Heiligenbrunner
 * @date 07.05.2020
 */

#pragma once

#include <string>

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
