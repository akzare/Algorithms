/*
 * @file   JosephusProblem.h
 * @author (original JAVA) Micah Stairs
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   15 July 2020
 * @version 0.1
 * @brief   An implementation of the Josephus problem Time complexity: O(n)
 */

#ifndef D_JOSEPHUSPROBLEM_H
#define D_JOSEPHUSPROBLEM_H

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

class JosephusProblem {
public:
  // Suppose there are n people in a circle and person
  // 0 kill the k'th person, then the k'th person kills
  // the 2k'th person and so on until only one person remains.
  // The question is who lives?
  // Let n be the number of people and k the hop size
  static int josephus(int n, int k) {
	std::vector<int> dp(n, 0);
    for (int i = 1; i < n; i++) dp[i] = (dp[i - 1] + k) % (i + 1);
    return dp[n - 1];
  }

};


void Josephusproblem_test()
{
  int n = 41, k = 2;
  std::cout << JosephusProblem::josephus(n, k) << std::endl;

  n = 25;
  k = 18;
  std::cout << JosephusProblem::josephus(n, k) << std::endl;

  n = 5;
  k = 2;
  std::cout << JosephusProblem::josephus(n, k) << std::endl;
}

} // namespace dsa

#endif /* D_JOSEPHUSPROBLEM_H */
