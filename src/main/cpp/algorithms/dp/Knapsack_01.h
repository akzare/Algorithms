/*
 * @file   Knapsack_01.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   15 July 2020
 * @version 0.1
 * @brief   This file contains a dynamic programming solutions to the classic 0/1 knapsack problem where are
 * you are trying to maximize the total profit of items selected without exceeding the capacity of
 * your knapsack.
 *
 * <p>Time Complexity: O(nW) Space Complexity: O(nW)
 *
 * <p>Tested code against: https://open.kattis.com/problems/knapsack
 */

#ifndef D_KNAPSACK01_H
#define D_KNAPSACK01_H

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

class Knapsack_01 {
public:
  /**
   * @param capacity - The maximum capacity of the knapsack
   * @param W - The weights of the items
   * @param V - The values of the items
   * @return The maximum achievable profit of selecting a subset of the elements such that the
   *     capacity of the knapsack is not exceeded
   */
  static int knapsack(int capacity, const std::vector<int>& W, const std::vector<int>& V, std::vector<int>& itemsSelected) {

    if (W.size() == 0 || W.size() != V.size() || capacity < 0)
      throw std::invalid_argument("Invalid input");

    int N = W.size();

    // Initialize a table where individual rows represent items
    // and columns represent the weight of the knapsack
    std::vector<std::vector<int>> DP(N + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= N; i++) {

      // Get the value and weight of the item
      int w = W[i - 1], v = V[i - 1];

      for (int sz = 1; sz <= capacity; sz++) {

        // Consider not picking this element
        DP[i][sz] = DP[i - 1][sz];

        // Consider including the current element and
        // see if this would be more profitable
        if (sz >= w && DP[i - 1][sz - w] + v > DP[i][sz]) DP[i][sz] = DP[i - 1][sz - w] + v;
      }
    }

    int sz = capacity;

    // Using the information inside the table we can backtrack and determine
    // which items were selected during the dynamic programming phase. The idea
    // is that if DP[i][sz] != DP[i-1][sz] then the item was selected
    for (int i = N; i > 0; i--) {
      if (DP[i][sz] != DP[i - 1][sz]) {
        int itemIndex = i - 1;
        itemsSelected.push_back(itemIndex);
        sz -= W[itemIndex];
      }
    }

    // Return the maximum profit
    return DP[N][capacity];
  }

};


void Knapsack01_test()
{
  {
  int capacity = 10;
  std::vector<int> V{1, 4, 8, 5};
  std::vector<int> W{3, 3, 5, 6};
  std::vector<int> itemsSelected;
  std::cout << Knapsack_01::knapsack(capacity, W, V, itemsSelected) << std::endl;
  }

  {
  int capacity = 7;
  std::vector<int> V{2, 2, 4, 5, 3};
  std::vector<int> W{3, 1, 3, 4, 2};
  std::vector<int> itemsSelected;
  std::cout << Knapsack_01::knapsack(capacity, W, V, itemsSelected) << std::endl;
  }
}

} // namespace dsa

#endif /* D_KNAPSACK01_H */
