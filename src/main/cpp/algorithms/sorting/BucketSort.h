/*
 * @file   BucketSort.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   13 July 2020
 * @version 0.1
 * @brief   Bucket sort implementation.
 */

#ifndef D_BUCKETSORT_H
#define D_BUCKETSORT_H

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

class BucketSort {

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
    bucketSort(values, minValue, maxValue);
  }


  // Performs a bucket sort of an array in which all the elements are
  // bounded in the range [minValue, maxValue]. For bucket sort to give linear
  // performance the elements need to be uniformly distributed
private:
  static void bucketSort(std::vector<int>& ar, int minValue, int maxValue) {
    if (ar.size() == 0 || minValue == maxValue) return;

    // N is number elements and M is the range of values
    int N = ar.size(), M = maxValue - minValue + 1, numBuckets = M / N + 1;
    std::vector<std::vector<int>> buckets(numBuckets);

    // Place each element in a bucket
    for (int i = 0; i < N; i++) {
      int bi = (ar[i] - minValue) / M;
      buckets[bi].push_back(ar[i]);
    }

    // Sort buckets and stitch together answer
    for (int bi = 0, j = 0; bi < numBuckets; bi++) {
      if (buckets[bi].size() != 0) {
        std::sort(buckets[bi].begin(), buckets[bi].end());
        for (unsigned k = 0; k < buckets[bi].size(); k++) {
          ar[j++] = buckets[bi][k];
        }
      }
    }
  }

};


// Example usage of Bucket Sort
int BucketSort_test()
{
  std::vector<int> array{10, 4, 6, 8, 13, 2, 3};
  BucketSort::sort(array);
  // Prints:
  // [2, 3, 4, 6, 8, 10, 13]
  std::cout << "[";
  for (auto a : array) std::cout << a << ",";
  std::cout << "]" << std::endl;


  array = std::vector<int>{10, 10, 10, 10, 10};
  BucketSort::sort(array);
  // Prints:
  // [10, 10, 10, 10, 10]
  std::cout << "[";
  for (auto a : array) std::cout << a << ",";
  std::cout << "]" << std::endl;

  return 0;
}


} // namespace dsa

#endif /* D_BUCKETSORT_H */
