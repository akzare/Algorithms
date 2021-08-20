/*
 * @file   LongestPalindromeSubsequence.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   14 July 2020
 * @version 0.1
 * @brief   Implementation of finding the longest paldindrome subsequence Time complexity: O(n^2)
 */

#ifndef D_LONGESTPALINDROMSUBSEQUENCETABULAR_H
#define D_LONGESTPALINDROMSUBSEQUENCETABULAR_H

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


class LongestPalindromeSubsequenceTabular {
public:
  // Returns the length of the longest palindrome subsequence
  // Using Bottom up Approach
  static int lps(const std::string& s) {
    if (s.length() == 0) return 0;
    std::vector<std::vector<int>> dp(s.length(), std::vector<int>(s.length(), 0));

    for(int l = 1; l <= s.length(); l++) {
      for(int i = 0; i <= s.length() - l; i++) {
        int j = i + l - 1;
        char c1 = s.at(i), c2 = s.at(j);

        //extra case for equal indices
        if(i == j) dp[i][j] = 1;
        //Handle out of bounds using ternary operator
        // Both end characters match 
        else if(c1 == c2) dp[i][j] = 2 + ((i + 1 < s.length() && j > 0) ? dp[i + 1][j - 1] : 0);
        // Consider both possible substrings and take the maximum
        else dp[i][j] = max((i + 1 < s.length()) ? dp[i + 1][j] : 0, (j > 0) ? dp[i][j - 1] : 0);
      }
    }

    return dp[0][s.length() - 1];
  }
};


void LongestPalindromeSubsequenceTabular_test()
{
  std::cout << LongestPalindromeSubsequenceTabular::lps("bbbab") << std::endl; // Outputs 4 since "bbbb" is valid soln
  std::cout << LongestPalindromeSubsequenceTabular::lps("bccd") << std::endl; // Outputs 2 since "cc" is valid soln
}


} // namespace dsa

#endif /* D_LONGESTPALINDROMSUBSEQUENCETABULAR_H */
