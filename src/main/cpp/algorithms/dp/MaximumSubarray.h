/*
 * @file   MaximumSubarray.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   14 July 2020
 * @version 0.1
 * @brief   This file shows you how to find the maximal subarray in an integer array Time complexity: O(n)
 */

#ifndef D_MAXSUBARRAY_H
#define D_MAXSUBARRAY_H

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


class MaximumSubarray {

public:
  // Return the value of the maximum subarray in 'ar'
  static long maximumSubarrayValue(const std::vector<int>& ar) {

    if (ar.size() == 0) return 0L;
    int n = ar.size(), maxValue, sum;

    maxValue = sum = ar[0];

    for (int i = 1; i < n; i++) {

      // At each step consider continuing the current subarray
      // or starting a new one because adding the next element
      // doesn't acutally make the subarray sum any better.
      if (ar[i] > sum + ar[i]) sum = ar[i];
      else sum = sum + ar[i];

      if (sum > maxValue) maxValue = sum;
    }

    return maxValue;
  }
};


void MaximumSubarray_test()
{
  std::cout << MaximumSubarray::maximumSubarrayValue(std::vector<int>{-5}) << std::endl;
  std::cout << MaximumSubarray::maximumSubarrayValue(std::vector<int>{-5, -4, -10, -3, -1, -12, -6}) << std::endl;
  std::cout << MaximumSubarray::maximumSubarrayValue(std::vector<int>{1, 2, 1, -7, 2, -1, 40, -89}) << std::endl;
}


} // namespace dsa

#endif /* D_MAXSUBARRAY_H */
