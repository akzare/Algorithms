/*
 * @file   LongestPalindromeSubsequence.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   14 July 2020
 * @version 0.1
 * @brief   Implementation of finding the longest paldindrome subsequence Time complexity: O(n^2)
 */

#ifndef D_LONGESTPALINDROMSUBSEQUENCE_H
#define D_LONGESTPALINDROMSUBSEQUENCE_H

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


class LongestPalindromeSubsequence {
public:
  // Returns the length of the longest paldindrome subsequence
  static int lps(const std::string& s) {
    if (s.length() == 0) return 0;
    std::vector<std::vector<int>> dp(s.length(), std::vector<int>(s.length(), 0));
    return lps(s, dp, 0, s.length() - 1);
  }


private:
  // Private recursive method with memoization to count
  // the longest paldindrome subsequence.
  static int lps(const std::string& s, std::vector<std::vector<int>>& dp, int i, int j) {

    // Base cases
    if (j < i) return 0;
    if (i == j) return 1;
    if (dp[i][j] != 0) return dp[i][j];

    char c1 = s.at(i), c2 = s.at(j);

    // Both end characters match
    if (c1 == c2) return dp[i][j] = lps(s, dp, i + 1, j - 1) + 2;

    // Consider both possible substrings and take the maximum
    return dp[i][j] = std::max(lps(s, dp, i + 1, j), lps(s, dp, i, j - 1));
  }
};


void LongestPalindromeSubsequence_test()
{
  std::cout << LongestPalindromeSubsequence::lps("bbbab") << std::endl; // Outputs 4 since "bbbb" is valid soln
  std::cout << LongestPalindromeSubsequence::lps("bccd") << std::endl; // Outputs 2 since "cc" is valid soln
}


} // namespace dsa

#endif /* D_LONGESTPALINDROMSUBSEQUENCE_H */
