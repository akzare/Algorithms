/*
 * @file   BitManipulationsTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   13 July 2020
 * @version 0.1
 * @brief   Bit manipulation operations unit test.
 */

#include <gtest\gtest.h>
#include <BitManipulations.h>
#include <UniqueCombinations.h>

#include <chrono>
#include <random>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>

namespace dsa {

TEST(BitManipulationsTest, testSetBit) {
  EXPECT_EQ(BitManipulations::setBit(0, 0), 0b1);
  EXPECT_EQ(BitManipulations::setBit(0, 1), 0b10);
  EXPECT_EQ(BitManipulations::setBit(0, 2), 0b100);
  EXPECT_EQ(BitManipulations::setBit(0, 3), 0b1000);
  EXPECT_EQ(BitManipulations::setBit(0, 4), 0b10000);
  EXPECT_EQ(BitManipulations::setBit(0, 5), 0b100000);
}


TEST(BitManipulationsTest, testPowerOfTwo) {
  EXPECT_FALSE(BitManipulations::isPowerOfTwo(0));
  EXPECT_FALSE(BitManipulations::isPowerOfTwo(-1));
  EXPECT_FALSE(BitManipulations::isPowerOfTwo(7));
  EXPECT_FALSE(BitManipulations::isPowerOfTwo(9));
  EXPECT_FALSE(BitManipulations::isPowerOfTwo(123456789));

  EXPECT_TRUE(BitManipulations::isPowerOfTwo(1));
  EXPECT_TRUE(BitManipulations::isPowerOfTwo(2));
  EXPECT_TRUE(BitManipulations::isPowerOfTwo(4));
  EXPECT_TRUE(BitManipulations::isPowerOfTwo(2048));
  EXPECT_TRUE(BitManipulations::isPowerOfTwo(1 << 20));
}


TEST(BitManipulationsTest, testClearBit) {
  EXPECT_EQ(BitManipulations::clearBit(0b0000, 1), 0);
  EXPECT_EQ(BitManipulations::clearBit(0b0100, 2), 0);
  EXPECT_EQ(BitManipulations::clearBit(0b0001, 0), 0);
  EXPECT_EQ(BitManipulations::clearBit(0b1111, 0), 14);
}


TEST(UniqueCombinationsTest, testCombinations) {
  UniqueCombunations_test();
}

} // namespace dsa
