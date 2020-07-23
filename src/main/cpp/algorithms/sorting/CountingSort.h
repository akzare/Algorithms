/*
 * @file   CountingSort.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   13 July 2020
 * @version 0.1
 * @brief   Counting sort implementation.
 */

#ifndef D_COUNTINGSORT_H
#define D_COUNTINGSORT_H

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


class CountingSort {

public:
  static void sort(std::vector<int>& values) {
    const int POSITIVE_INFINITY = std::numeric_limits<int>::infinity();
    const int NEGATIVE_INFINITY = -std::numeric_limits<int>::infinity();
    int minValue = POSITIVE_INFINITY;
    int maxValue = NEGATIVE_INFINITY;
    for (unsigned i = 0; i < values.size(); i++) {
      if (values[i] < minValue) minValue = values[i];
      if (values[i] > maxValue) maxValue = values[i];
    }
    countingSort(values, minValue, maxValue);
  }


private:
  // Sorts values in the range of [minVal, maxVal] in O(n+maxVal-maxVal)
  static void countingSort(std::vector<int>& ar, int minVal, int maxVal) {
    int sz = maxVal - minVal + 1;
    std::vector<int> b(sz, 0);
    for (unsigned i = 0; i < ar.size(); i++) b[ar[i] - minVal]++;
    for (int i = 0, k = 0; i < sz; i++) {
      while (b[i]-- > 0) ar[k++] = i + minVal;
    }
  }

};


// Example usage of Counting Sort
int CountingSort_test()
{
  std::vector<int> nums{+4, -10, +0, +6, +1, -5, -5, +1, +1, -2, 0, +6, +8, -7, +10};
  CountingSort::sort(nums);

  // Prints:
  // [-10, -7, -5, -5, -2, 0, 0, 1, 1, 1, 4, 6, 6, 8, 10]
  std::cout << "[";
  for (auto a : nums) std::cout << a << ",";
  std::cout << "]" << std::endl;

  return 0;
}


} // namespace dsa

#endif /* D_COUNTINGSORT_H */
