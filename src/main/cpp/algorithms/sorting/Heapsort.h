/*
 * @file   Heapsort.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   13 July 2020
 * @version 0.1
 * @brief   Heap sort implementation.
 */

#ifndef D_HEAPSORT_H
#define D_HEAPSORT_H

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

class Heapsort {

public:
  static void sort(std::vector<int>& values) {
    heapsort(values);
  }


private:
  static void heapsort(std::vector<int>& ar) {
    if (ar.size() == 0) return;
    int n = ar.size();

    // Heapify, converts array into binary heap O(n), see:
    // http://www.cs.umd.edu/~meesh/351/mount/lectures/lect14-heapsort-analysis-part.pdf
    for (int i = std::max(0, (n / 2) - 1); i >= 0; i--) {
      sink(ar, n, i);
    }

    // Sorting bit
    for (int i = n - 1; i >= 0; i--) {
      swap(ar, 0, i);
      sink(ar, i, 0);
    }
  }


  static void sink(std::vector<int>& ar, int n, int i) {
    while (true) {
      int left = 2 * i + 1; // Left  node
      int right = 2 * i + 2; // Right node
      int largest = i;

      // Right child is larger than parent
      if (right < n && ar[right] > ar[largest]) largest = right;

      // Left child is larger than parent
      if (left < n && ar[left] > ar[largest]) largest = left;

      // Move down the tree following the largest node
      if (largest != i) {
        swap(ar, largest, i);
        i = largest;
      } else break;
    }
  }


  static void swap(std::vector<int>& ar, int i, int j) {
    int tmp = ar[i];
    ar[i] = ar[j];
    ar[j] = tmp;
  }

};


// Example usage of Heap Sort
int HeapSort_test()
{
  std::vector<int> array{10, 4, 6, 4, 8, -13, 2, 3};
  Heapsort::sort(array);
  // Prints:
  // [-13, 2, 3, 4, 4, 6, 8, 10]
  std::cout << "[";
  for (auto a : array) std::cout << a << ",";
  std::cout << "]" << std::endl;

  return 0;
}

} // namespace dsa

#endif /* D_HEAPSORT_H */
