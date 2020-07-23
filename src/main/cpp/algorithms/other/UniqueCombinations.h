/*
 * @file   UniqueCombinations.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   13 July 2020
 * @version 0.1
 * @brief
 * This file shows you how to generate all the unique combinations of a set even though some
 * elements may be repeated. For example, if your set is {2, 2, 3, 3, 3} and you care only about
 * sets of size two (r = 2) then the unique sets are {{2,2}, {2,3}, {3,3}}.
 *
 * <p>Time Complexity: O( n choose r )
 */

#ifndef D_UNIQUECOMBINATIONS_H
#define D_UNIQUECOMBINATIONS_H

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

namespace dsa {

class UniqueCombinations {

public:
  static void combinations(const std::vector<int>& set, int r) {

    if (set.size() == 0) return;
    if (r < 0) return;

    // Sort the numbers so we can easily skip duplicates.
    std::vector<int> set_cpy = set;
    std::sort(set_cpy.begin(), set_cpy.end());

    std::vector<bool> used(set.size(), false);
    combinations(0, r, used, set);
  }

private:
  static void combinations(int at, int r, std::vector<bool> &used, const std::vector<int>& set) {

    int n = set.size();

    // We select 'r' elements so we found a valid subset!
    if (r == 0) {

      std::vector<int> subset;
      for (int i = 0; i < n; i++) if (used[i]) subset.push_back(set[i]);
      std::cout << "[";
      for (auto s : subset) std::cout << s << ",";
      std::cout << "]" << std::endl;

    } else {
      for (int i = at; i < n; i++) {

        // Since the elements are sorted we can skip duplicate
        // elements to ensure the uniqueness of our output.
        if (i > at && set[i - 1] == set[i]) continue;

        used[i] = true;
        combinations(i + 1, r - 1, used, set);
        used[i] = false;
      }
    }
  }

};


// Example usage of Unique Combunations
int UniqueCombunations_test()
{
  // Example #1
  int r = 2;
  std::vector<int> set{2, 3, 3, 2, 3};
  UniqueCombinations::combinations(set, r);
  // Prints:
  // [2, 2]
  // [2, 3]
  // [3, 3]


  r = 3;
  set = std::vector<int>{1, 2, 2, 2, 3, 3, 4, 4};
  UniqueCombinations::combinations(set, r);
  // Prints:
  // [1, 2, 2]
  // [1, 2, 3]
  // [1, 2, 4]
  // [1, 3, 3]
  // [1, 3, 4]
  // [1, 4, 4]
  // [2, 2, 2]
  // [2, 2, 3]
  // [2, 2, 4]
  // [2, 3, 3]
  // [2, 3, 4]
  // [2, 4, 4]
  // [3, 3, 4]
  // [3, 4, 4]

  return 0;
}

} // namespace dsa

#endif /* D_UNIQUECOMBINATIONS_H */
