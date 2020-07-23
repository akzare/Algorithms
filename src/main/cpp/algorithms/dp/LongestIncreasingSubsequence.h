/*
 * @file   LongestIncreasingSubsequence.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   14 July 2020
 * @version 0.1
 * @brief   This file shows you how to find the length of the longest increasing subsequence length, using
 * dynamic programming. Time complexity: O(n^2)
 */

#ifndef D_LONGESTINCREASINGSUBSEQUENCE_H
#define D_LONGESTINCREASINGSUBSEQUENCE_H

#include <vector>
#include <deque>
#include <list>
#include <set>   // set and multiset
#include <map>   // map and multimap
#include <unordered_set>  // unordered set/multiset
#include <unordered_map>  // unordered map/multimap
#include <iterator>
#include <algorithm>
#include <numeric>    // some numeric algorithm
#include <functional>
#include <stack>

#include <sstream>
#include <memory>
#include <iostream>
#include <cmath>

namespace dsa {


class LongestIncreasingSubsequence {

public:

  // Finds the length of the longest increasing subsequence length, O(n^2)
  static int lis(const std::vector<int>& ar) {

    if (ar.size() == 0) return 0;
    int n = ar.size(), len = 0;

    // When starting, each individual element has a LIS
    // of exactly one, so each index is initialized to 1
    std::vector<int> dp(n, 1);

    // Processing the array left to right update the value of dp[j] if two
    // conditions hold 1) The value at i is less than that of the one at j
    // and 2) updating the value of dp[j] to dp[i]+1 is better
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        if (ar[i] < ar[j] && dp[j] < dp[i] + 1) {
          dp[j] = dp[i] + 1;
        }
      }
      // Track the LIS
      if (dp[i] > len) len = dp[i];
    }

    return len;
  }
};


void LongestIncreasingSubsequence_test()
{
  std::cout << LongestIncreasingSubsequence::lis(std::vector<int>{1, 3, 2, 4, 3}) << std::endl; // 3
  std::cout << LongestIncreasingSubsequence::lis(std::vector<int>{2, 7, 4, 3, 8}) << std::endl; // 3
  std::cout << LongestIncreasingSubsequence::lis(std::vector<int>{5, 4, 3, 2, 1}) << std::endl; // 1
  std::cout << LongestIncreasingSubsequence::lis(std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}) << std::endl; // 9
}


} // namespace dsa

#endif /* D_LONGESTINCREASINGSUBSEQUENCE_H */
