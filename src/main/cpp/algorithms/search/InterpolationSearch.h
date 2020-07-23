/*
 * @file   InterpolationSearch.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   14 July 2020
 * @version 0.1
 * @brief   An implementation of interpolation search.
 * <p>Time Complexity: O(log(log(n))) if data is uniform O(n) in worst case
 */

#ifndef D_INTERPOLATIONSEARCH_H
#define D_INTERPOLATIONSEARCH_H

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


class InterpolationSearch {

public:
  /**
   * A fast alternative to a binary search when the elements are uniformly distributed. This
   * algorithm runs in a time complexity of ~O(log(log(n))).
   *
   * @param nums - an ordered list containing uniformly distributed values.
   * @param val - the value we're looking for in 'nums'
   */
   static int interpolationSearch(const std::vector<int>& nums, int val) {
    int lo = 0, mid = 0, hi = nums.size() - 1;
    while (nums[lo] <= val && nums[hi] >= val) {
      mid = lo + ((val - nums[lo]) * (hi - lo)) / (nums[hi] - nums[lo]);
      if (nums[mid] < val) {
        lo = mid + 1;
      } else if (nums[mid] > val) {
        hi = mid - 1;
      } else return mid;
    }
    if (nums[lo] == val) return lo;
    return -1;
  }

};


// Example usage of Interpolation search
int InterpolationSearch_test()
{
  std::vector<int> values{10, 20, 25, 35, 50, 70, 85, 100, 110, 120, 125};

  // Since 25 exists in the values array the interpolation search
  // returns that it has found 25 at the index 2
  std::cout << InterpolationSearch::interpolationSearch(values, 25) << std::endl;

  // 111 does not exist so we get -1 as an index value
  std::cout << InterpolationSearch::interpolationSearch(values, 111) << std::endl;

  return 0;
}

} // namespace dsa

#endif /* D_INTERPOLATIONSEARCH_H */
