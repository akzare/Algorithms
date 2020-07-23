/*
 * @file   LongestCommonSubstring.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   14 July 2020
 * @version 0.1
 * @brief   This file contains an implementation of finding the Longest Common Substring (LCS) between two
 * strings using dynamic programming.
 *
 * <p>Time Complexity: O(nm)
 */

#ifndef D_LONGESTCOMMONSUBSTRING_H
#define D_LONGESTCOMMONSUBSTRING_H

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

class LongestCommonSubstring {

public:
  // Returns a non unique Longest Common Substring
  // between the strings str1 and str2 in O(nm)
  static std::string lcs(const std::vector<char>& A, const std::vector<char>& B) {

    if (A.size() == 0 || B.size() == 0) return std::string();

    int n = A.size();
    int m = B.size();

    if (n == 0 || m == 0) return std::string();

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));

    // Suppose A = a1a2..an-1an and B = b1b2..bn-1bn
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {

        // If ends match the LCS(a1a2..an-1an, b1b2..bn-1bn) = LCS(a1a2..an-1, b1b2..bn-1) + 1
        if (A[i - 1] == B[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;

        // If the ends do not match the LCS of a1a2..an-1an and b1b2..bn-1bn is
        // max( LCS(a1a2..an-1, b1b2..bn-1bn), LCS(a1a2..an-1an, b1b2..bn-1) )
        else dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }

    int lcsLen = dp[n][m];
    std::vector<char> lcs(lcsLen);
    int index = 0;

    // Backtrack to find a LCS. We search for the cells
    // where we included an element which are those with
    // dp[i][j] != dp[i-1][j] and dp[i][j] != dp[i][j-1])
    int i = n, j = m;
    while (i >= 1 && j >= 1) {

      int v = dp[i][j];

      // The order of these may output different LCSs
      while (i > 1 && dp[i - 1][j] == v) i--;
      while (j > 1 && dp[i][j - 1] == v) j--;

      // Make sure there is a match before adding
      if (v > 0) lcs[lcsLen - index++ - 1] = A[i - 1]; // or B[j-1];

      i--;
      j--;
    }

    return std::string(lcs.begin(), lcs.end());
  }

};


void LongestCommonSubstring_test()
{
  {
  std::vector<char> A{'A', 'X', 'B', 'C', 'Y'};
  std::vector<char> B{'Z', 'A', 'Y', 'W', 'B', 'C'};
  std::cout << LongestCommonSubstring::lcs(A, B) << std::endl; // ABC
  }

  {
  std::vector<char> A{'3', '9', '8', '3', '9', '7', '9', '7', '0'};
  std::vector<char> B{'3', '3', '9', '9', '9', '1', '7', '2', '0', '6'};
  std::cout << LongestCommonSubstring::lcs(A, B) << std::endl; // 339970
  }
}

} // namespace dsa

#endif /* D_LONGESTCOMMONSUBSTRING_H */
