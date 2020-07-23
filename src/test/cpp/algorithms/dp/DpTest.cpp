/*
 * @file   DpTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   14 July 2020
 * @version 0.1
 * @brief   Test all dynamic programming algorithms under various constraints.
 */

#include <gtest\gtest.h>
#include <LongestPalindromeSubsequence.h>
#include <MaximumSubarray.h>
#include <LongestIncreasingSubsequence.h>
#include <LongestCommonSubstring.h>
#include <Knapsack_01.h>
#include <KnapsackUnbounded.h>
#include <JosephusProblem.h>
#include <CoinChange.h>

#include <chrono>
#include <random>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>
#include <array>

namespace dsa {

TEST(LongestPalindromeSubsequenceTest, testSample) {
  EXPECT_EQ(LongestPalindromeSubsequence::lps("bbbab"), 4); // Outputs 4 since "bbbb" is valid soln
  EXPECT_EQ(LongestPalindromeSubsequence::lps("bccd"), 2); // Outputs 2 since "cc" is valid soln
}


TEST(MaximumSubarrayTest, testSample) {
  EXPECT_EQ(MaximumSubarray::maximumSubarrayValue(std::vector<int>{-5}), -5);
  EXPECT_EQ(MaximumSubarray::maximumSubarrayValue(std::vector<int>{-5, -4, -10, -3, -1, -12, -6}), -1);
  EXPECT_EQ(MaximumSubarray::maximumSubarrayValue(std::vector<int>{1, 2, 1, -7, 2, -1, 40, -89}), 41);
}


TEST(LongestIncreasingSubsequenceTest, testSample) {
  EXPECT_EQ(LongestIncreasingSubsequence::lis(std::vector<int>{1, 3, 2, 4, 3}), 3); // 3
  EXPECT_EQ(LongestIncreasingSubsequence::lis(std::vector<int>{2, 7, 4, 3, 8}), 3); // 3
  EXPECT_EQ(LongestIncreasingSubsequence::lis(std::vector<int>{5, 4, 3, 2, 1}), 1); // 1
  EXPECT_EQ(LongestIncreasingSubsequence::lis(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}), 9); // 9
}


TEST(LongestCommonSubstringTest, testSample) {
  {
  std::vector<char> A{'A', 'X', 'B', 'C', 'Y'};
  std::vector<char> B{'Z', 'A', 'Y', 'W', 'B', 'C'};
  EXPECT_EQ(LongestCommonSubstring::lcs(A, B), "ABC");
  }

  {
  std::vector<char> A{'3', '9', '8', '3', '9', '7', '9', '7', '0'};
  std::vector<char> B{'3', '3', '9', '9', '9', '1', '7', '2', '0', '6'};
  EXPECT_EQ(LongestCommonSubstring::lcs(A, B), "339970");
  }
}


TEST(Knapsack01Test, testSample) {
  {
  int capacity = 10;
  std::vector<int> V{1, 4, 8, 5};
  std::vector<int> W{3, 3, 5, 6};
  std::vector<int> itemsSel;
  std::vector<int> itemsSelExpect{2, 1};
  EXPECT_EQ(Knapsack_01::knapsack(capacity, W, V, itemsSel), 12);
  EXPECT_EQ(itemsSel, itemsSelExpect);
  }

  {
  int capacity = 7;
  std::vector<int> V{2, 2, 4, 5, 3};
  std::vector<int> W{3, 1, 3, 4, 2};
  std::vector<int> itemsSel;
  std::vector<int> itemsSelExpect{4, 3, 1};
  EXPECT_EQ(Knapsack_01::knapsack(capacity, W, V, itemsSel), 10);
  EXPECT_EQ(itemsSel, itemsSelExpect);
  }
}


TEST(UnboundedKnapsackTest, testSample) {
  std::vector<int> W{3, 6, 2};
  std::vector<int> V{5, 20, 3};
  int knapsackValue = KnapsackUnbounded::unboundedKnapsackSpaceEfficient(10, W, V);
  std::cout << "Maximum knapsack value: " << knapsackValue << std::endl;
  EXPECT_EQ(knapsackValue, 26);
}


TEST(JosephusProblemTest, testSample) {
  int n = 41, k = 2;
  EXPECT_EQ(JosephusProblem::josephus(n, k), 18);

  n = 25;
  k = 18;
  EXPECT_EQ(JosephusProblem::josephus(n, k), 1);

  n = 5;
  k = 2;
  EXPECT_EQ(JosephusProblem::josephus(n, k), 2);
}


TEST(CoinChangeTest, testSample) {
  const std::vector<int> coins{2, 6, 1};
  EXPECT_EQ(CoinChange::coinChange(coins, 17), 5);
  EXPECT_EQ(CoinChange::coinChangeSpaceEfficient(coins, 17), 5);
  EXPECT_EQ(CoinChange::coinChangeRecursive(coins, 17), 5);
}

} // namespace dsa
