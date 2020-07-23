/*
 * @file   KnapsackUnbounded.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   15 July 2020
 * @version 0.1
 * @brief   This file contains a dynamic programming solutions to the classic unbounded knapsack problem
 * where are you are trying to maximize the total profit of items selected without exceeding the
 * capacity of your knapsack.
 *
 * <p>Version 1: Time Complexity: O(nW) Version 1 Space Complexity: O(nW)
 *
 * <p>Version 2: Time Complexity: O(nW) Space Complexity: O(W)
 *
 * <p>Tested code against: https://www.hackerrank.com/challenges/unbounded-knapsack
 */

#ifndef D_KNAPSACKUNBOUNDED_H
#define D_KNAPSACKUNBOUNDED_H

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

class KnapsackUnbounded {
public:
  /**
   * @param maxWeight - The maximum weight of the knapsack
   * @param W - The weights of the items
   * @param V - The values of the items
   * @return The maximum achievable profit of selecting a subset of the elements such that the
   *     capacity of the knapsack is not exceeded
   */
  static int unboundedKnapsack(int maxWeight, const std::vector<int>& W, const std::vector<int>& V) {

    if (W.size() == 0 || W.size() != V.size() || maxWeight < 0)
      throw std::invalid_argument("Invalid input");

    int N = W.size();

    // Initialize a table where individual rows represent items
    // and columns represent the weight of the knapsack
    std::vector<std::vector<int>> DP(N + 1, std::vector<int>(maxWeight + 1, 0));

    // Loop through items
    for (int i = 1; i <= N; i++) {

      // Get the value and weight of the item
      int w = W[i - 1], v = V[i - 1];

      // Consider all possible knapsack sizes
      for (int sz = 1; sz <= maxWeight; sz++) {

        // Try including the current element
        if (sz >= w) DP[i][sz] = DP[i][sz - w] + v;

        // Check if not selecting this item at all is more profitable
        if (DP[i - 1][sz] > DP[i][sz]) DP[i][sz] = DP[i - 1][sz];
      }
    }

    // Return the best value achievable
    return DP[N][maxWeight];
  }


public:
  static int unboundedKnapsackSpaceEfficient(int maxWeight, const std::vector<int>& W, const std::vector<int>& V) {

    if (W.size() == 0 || W.size() != V.size() || maxWeight < 0)
      throw std::invalid_argument("Invalid input");

    int N = W.size();

    // Initialize a table where we will only keep track of
    // the best possible value for each knapsack weight
    std::vector<int> DP(maxWeight + 1, 0);

    // Consider all possible knapsack sizes
    for (int sz = 1; sz <= maxWeight; sz++) {

      // Loop through items
      for (int i = 0; i < N; i++) {

        // First check that we can include this item (we can't include it if
        // it's too heavy for our knapsack). Assumming it fits inside the
        // knapsack check if including this element would be profitable.
        if (sz - W[i] >= 0 && DP[sz - W[i]] + V[i] > DP[sz]) DP[sz] = DP[sz - W[i]] + V[i];
      }
    }

    // Return the best value achievable
    return DP[maxWeight];
  }

};


void UnboundedKnapsack_test()
{
  std::vector<int> W{3, 6, 2};
  std::vector<int> V{5, 20, 3};
  int knapsackValue = KnapsackUnbounded::unboundedKnapsackSpaceEfficient(10, W, V);
  std::cout << "Maximum knapsack value: " << knapsackValue << std::endl;
}

} // namespace dsa

#endif /* D_KNAPSACKUNBOUNDED_H */
