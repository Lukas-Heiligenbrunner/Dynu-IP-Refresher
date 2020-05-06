//
// Created by lukas on 06.05.20.
//

#include "gtest/gtest.h"
#include "IPRefresher.h"

TEST (SquareTest /*test suite name*/, LukisTest /*test name*/) {
//EXPECT_EQ (9.0, (3.0*3.0)); // fail, test continues
ASSERT_EQ (0.0, (0.0));     // success
//ASSERT_EQ (9, (3)*(-3.0));  // fail, test interrupts
//ASSERT_EQ (-9, (-3)*(-3.0));// not executed due to the previous assert
}

TEST(Bla, test2){
    ASSERT_EQ(5.0,5.0);
}

TEST(Bla, test5){
    ASSERT_EQ(4.0,5.0);
}

TEST(IPRefresher, test1){
    IPRefresher ipr;

    ASSERT_EQ(5.0,5.0);
}