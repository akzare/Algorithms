/*
 * @file   QuickSort3.h
 * @author (original JAVA) Atharva Thorve, aaathorve@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   13 July 2020
 * @version 0.1
 * @brief   Quick sort implementation.
 * QuickSort3 or Dutch National Flag algorithm is similar to the QuickSort algorithm but has an
 * improved partitioning algorithm. QuickSort is quite slow in the case where very few unique
 * elements exist in the array so the QuickSort3 algorithm is used at that time.
 */

#ifndef D_QUICK3SORT_H
#define D_QUICK3SORT_H

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

#include <chrono>
#include <random>
#include <sstream>
#include <memory>
#include <iostream>

namespace dsa {

class QuickSort3 {

public:
  static void sort(std::vector<int>& values) {
    if (values.size() == 0) return;
    randomizedQuickSort(values, 0, values.size() - 1);
  }


private:

  static int genRandInt(int start_in, int end_in)
  {
    // engine only provides a source of randomness
    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    std::uniform_int_distribution<int> dist(start_in, end_in);

    return dist(rng);
  }


  // partiton array in such a way that all the elements whose value is equal to
  // pivot are grouped together
  static std::vector<int> partition3(std::vector<int>& a, int l, int r) {
    int j, k;
    if (r - l <= 1) {
      if (a[r] < a[l]) {
        swap(a, l, r);
      }
      j = l;
      k = r;
      std::vector<int> m{j, k};
      return std::move(m);
    }
    int mid = l;
    int p = a[r];
    while (mid <= r) {
      if (a[mid] < p) {
        swap(a, l, mid);
        l++;
        mid++;
      } else if (a[mid] == p) {
        mid++;
      } else {
        swap(a, mid, r);
        r--;
      }
    }
    j = l - 1;
    k = mid;
    std::vector<int> m{j, k};
    return std::move(m);
  }


  // Sort interval [lo, hi] inplace recursively
  // This chooses random pivot value thus improving time complexity
  static void randomizedQuickSort(std::vector<int>& a, int l, int r) {
    if (l >= r) {
      return;
    }
    int k = genRandInt(0, r - l + 1) + l;
    int t = a[l];
    a[l] = a[k];
    a[k] = t;
    // use partition3
    std::vector<int> m = partition3(a, l, r);
    randomizedQuickSort(a, l, m[0]);
    randomizedQuickSort(a, m[1], r);
  }


  // Swap two elements
  static void swap(std::vector<int>& ar, int i, int j) {
    int tmp = ar[i];
    ar[i] = ar[j];
    ar[j] = tmp;
  }

};


// Example usage of Quick3 Sort
int Quick3Sort_test()
{
  std::vector<int> array = {10, 4, 6, 4, 8, -13, 2, 3};
  QuickSort3::sort(array);
  // Prints:
  // [-13, 2, 3, 4, 4, 6, 8, 10]
  std::cout << "[";
  for (auto a : array) std::cout << a << ",";
  std::cout << "]" << std::endl;

  return 0;
}


} // namespace dsa

#endif /* D_QUICK3SORT_H */
