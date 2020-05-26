//
// Created by lukas on 06.05.20.
//

#include <FileLogger.h>
#include <api/IPAPI.h>
#include "gtest/gtest.h"

/**
 * Test if default ip is 0.0.0.0 when last ip file doesn't exist.
 */
TEST(ReadIp, testzeroIpIfNotExists) {
    FileLogger logger;
    std::string oldip = logger.readip();
    ASSERT_EQ(oldip, "0.0.0.0");
}
/**
 * Test if default ip is 0.0.0.0 when last ip file doesn't exist.
 */
TEST(IPAPI, testIpAPIcheckIPSyntax) {
    IPAPI ipapi;
    std::string ip = ipapi.getGlobalIp();
    if (ip.find('.') == SIZE_MAX) {
        // error when ip doesn't contain a .
        ASSERT_TRUE(false);
    } else {
        ASSERT_TRUE(true);
    }
}