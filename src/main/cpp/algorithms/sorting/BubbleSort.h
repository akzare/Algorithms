/*
 * @file   BubbleSort.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   13 July 2020
 * @version 0.1
 * @brief   Bubble sort implementation.
 */

#ifndef D_BUBBLESORT_H
#define D_BUBBLESORT_H

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

class BubbleSort {
public:
  static void sort(std::vector<int>& values) {
    bubbleSort(values);
  }


  // Sort the array using bubble sort. The idea behind
  // bubble sort is to look for adjacent indexes which
  // are out of place and interchange their elements
  // until the entire array is sorted.
private:
  static void bubbleSort(std::vector<int>& ar) {
    if (ar.size() == 0) {
      return;
    }

    bool sorted;
    do {
      sorted = true;
      for (unsigned i = 1; i < ar.size(); i++) {
        if (ar[i] < ar[i - 1]) {
          swap(ar, i - 1, i);
          sorted = false;
        }
      }
    } while (!sorted);
  }


  static void swap(std::vector<int>& ar, int i, int j) {
    int tmp = ar[i];
    ar[i] = ar[j];
    ar[j] = tmp;
  }
};


// Example usage of Bubble Sort
int BubbleSort_test()
{
  std::vector<int> array{10, 4, 6, 8, 13, 2, 3};
  BubbleSort::sort(array);
  // Prints:
  // [2, 3, 4, 6, 8, 10, 13]
  std::cout << "[";
  for (auto a : array) std::cout << a << ",";
  std::cout << "]" << std::endl;
  return 0;
}

} // namespace dsa

#endif /* D_BUBBLESORT_H */
