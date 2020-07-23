/*
 * @file   TspDynamicProgrammingIterative.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   11 July 2020
 * @version 0.1
 * @brief   An implementation of the traveling salesman problem using dynamic programming to improve
 * the time complexity from O(n!) to O(n^2 * 2^n).
 *
 * Time Complexity: O(n^2 * 2^n) Space Complexity: O(n * 2^n)
 *
 * # Finds the minimum TSP tour cost.
 * # m - 2D adjacency matrix representing graph
 * # S - The start node (0 <= S < N)
 * function tsp(m, S):
 *   N = matrix.size
 *
 *   # Initialize memo table.
 *   # Fill table with null values or +inf
 *   memo = 2D table of size N by 2^N
 *
 *   setup(m, memo, S, N)
 *   solve(m, memo, S, N)
 *   minCost = findMinCost(m, memo, S, N)
 *   tour = findOptimalTour(m, memo, S, N)
 *
 *   return (minCost, tour)
 *
 *
 * # Initialize the memo table by caching
 * # the optimal solution from the start
 * # node to every other node.
 * function setup(m, memo, S, N):
 *   for (i=0; i<N; i=i+1):
 *     if i == S: continue
 *
 *     # Store the optimal value from node S
 *     # to each node i (this is given as input)
 *     # in the adjacency matrix m).
 *     memo[i][1 << S | 1 << i] = m[S][i]
 *
 *
 * function solve(m, memo, S, N):
 *   for (r=3; r<=N; r++):
 *     # The combinations function generates all bit sets
 *     # of size N with r bits set to 1. For example,
 *     # combinations(3,4)={0111, 1011, 1101, 1110}
 *     for subset in combinations(r, N):
 *       if notIn(S, subset): continue
 *         for (next = 0; next < N; next = next + 1):
 *           if next == S || notIn(next, subset): continue
 *           # The subset state without the next node
 *           state = subset ^ (1 << next)
 *           minDist = +inf
 *           # 'e' is short for end node.
 *           for (e = 0; e < N; e = e + 1):
 *             if e == S || e == next || notIn(e, subset): continue
 *             newDistance = memo[e][state] + m[e][next]
 *             if (newDistance < minDist): minDist = newDistance
 *           memo[next][subset] = minDist
 *
 *
 * # Returns true if the i'th bit in 'subset' is not set
 * function notIn(i, subset):
 *   return ((1 << i) & subset) == 0
 *
 *
 * # Generate all bit sets of size n with r bits set to 1.
 * function combinations(r, n):
 *   subsets = []
 *   combinations(0, 0, r, n, subsets)
 *   return subsets
 *
 *
 * # Recursive method to generate bit sets.
 * function combinations(set, at, r, n, subsets):
 *   if r == 0:
 *     subsets.add(set)
 *   else:
 *     for (i=at; i<n; i=i+1):
 *       # Flip on i'th bit
 *       set = set | (1 << i)
 *
 *       combinations(set, i+1, r-1, n, subsets)
 *
 *       # Backtrack and flip off i'th bit
 *       set = set & ~(1 << i)
 *
 *
 * function findMinCost(m, memo, S, N):
 *   # The end state is the bit mask with
 *   # N bits set to 1 (equivalently 2^N - 1)
 *   END_STATE = (1 << N) - 1
 *
 *   minTourCost = +inf
 *
 *   for (e=0; e<N; e=e+1):
 *     if e == S: continue
 *
 *     tourCost = memo[e][END_STATE] + m[e][S]
 *     if tourCost < minTourCost:
 *       minTourCost = tourCost
 *
 *   return minTourCost
 *
 *
 * function findOptimalTour(m, memo, S, N):
 *   lastIndex = S
 *   state = (1 << N) - 1; # End state
 *   tour = array of size N+1
 *
 *   for (i = N-1; i >= 1; i--):
 *     index = -1
 *     for (j = 0; j < N; j++):
 *       if j == S | notIn(j, state): continue
 *       if (index == -1) index = j
 *       prevDist = memo[index][state] + m[index][lastIndex]
 *       newDist = memo[j][state] + m[j][lastIndex];
 *       if (newDist < prevDist) index = j
 *
 *     tour[i] = index
 *     state = state ^ (1 << index)
 *     lastIndex = index
 *
 *   tour[0] = tour[N] = S
 *   return tour
 */

#ifndef D_GRAPH_TSPDYNAMICPROGITER_H
#define D_GRAPH_TSPDYNAMICPROGITER_H

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
#include <limits>
#include <cassert>
#include <stdexcept>


namespace dsa {

class TspDynamicProgrammingIterative {
private:
  const double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
  const double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();

  int N_, start_;
  std::vector<std::vector<double> > distance_;
  std::list<int> tour_;
  double minTourCost_;
  bool ranSolver_;


private:

  bool notIn(int elem, int subset) {
    return ((1 << elem) & subset) == 0;
  }


  // This method generates all bit sets of size n where r bits
  // are set to one. The result is returned as a list of integer masks.
  std::list<int> combinations(int r, int n) {
    std::list<int> subsets;
    combinations(0, 0, r, n, subsets);
    return subsets;
  }


  // To find all the combinations of size r we need to recurse until we have
  // selected r elements (aka r = 0), otherwise if r != 0 then we still need to select
  // an element which is found after the position of our last selected element
  void combinations(int set, int at, int r, int n, std::list<int>& subsets) {

    // Return early if there are more elements left to select than what is available.
    int elementsLeftToPick = n - at;
    if (elementsLeftToPick < r) return;

    // We selected 'r' elements so we found a valid subset!
    if (r == 0) {
      subsets.push_back(set);
    } else {
      for (int i = at; i < n; i++) {
        // Try including this element
        set ^= (1 << i);

        combinations(set, i + 1, r - 1, n, subsets);

        // Backtrack and try the instance where we did not include this element
        set ^= (1 << i);
      }
    }
  }


  // Solves the traveling salesman problem and caches solution.
  void solve() {

    if (ranSolver_) return;

    int END_STATE = (1 << N_) - 1;
    std::vector<std::vector<double>> memo(N_ , std::vector<double> (1 << N_, POSITIVE_INFINITY));

    // Add all outgoing edges from the starting node to memo table.
    for (int end = 0; end < N_; end++) {
      if (end == start_) continue;
      memo[end][(1 << start_) | (1 << end)] = distance_[start_][end];
    }

    for (int r = 3; r <= N_; r++) {
      for (int subset : combinations(r, N_)) {
        if (notIn(start_, subset)) continue;
        for (int next = 0; next < N_; next++) {
          if (next == start_ || notIn(next, subset)) continue;
          int subsetWithoutNext = subset ^ (1 << next);
          double minDist = POSITIVE_INFINITY;
          for (int end = 0; end < N_; end++) {
            if (end == start_ || end == next || notIn(end, subset)) continue;
            double newDistance = memo[end][subsetWithoutNext] + distance_[end][next];
            if (newDistance < minDist) {
              minDist = newDistance;
            }
          }
          memo[next][subset] = minDist;
        }
      }
    }

    // Connect tour back to starting node and minimize cost.
    for (int i = 0; i < N_; i++) {
      if (i == start_) continue;
      double tourCost = memo[i][END_STATE] + distance_[i][start_];
      if (tourCost < minTourCost_) {
        minTourCost_ = tourCost;
      }
    }

    int lastIndex = start_;
    int state = END_STATE;
    tour_.push_front(start_);

    // Reconstruct TSP path from memo table.
    for (int i = 1; i < N_; i++) {

      int index = -1;
      for (int j = 0; j < N_; j++) {
        if (j == start_ || notIn(j, state)) continue;
        if (index == -1) index = j;
        double prevDist = memo[index][state] + distance_[index][lastIndex];
        double newDist = memo[j][state] + distance_[j][lastIndex];
        if (newDist < prevDist) {
          index = j;
        }
      }

      tour_.push_front(index);
      state = state ^ (1 << index);
      lastIndex = index;
    }

    tour_.push_front(start_);

    ranSolver_ = true;
  }

public:
  TspDynamicProgrammingIterative(const TspDynamicProgrammingIterative&) = delete;
  TspDynamicProgrammingIterative& operator=(TspDynamicProgrammingIterative const&) = delete;

  TspDynamicProgrammingIterative(std::vector<std::vector<double>>& distance) :  TspDynamicProgrammingIterative(0, distance) {}


  TspDynamicProgrammingIterative(int start, std::vector<std::vector<double>>& distance) {
    minTourCost_ = POSITIVE_INFINITY;
    ranSolver_ = false;
    N_ = distance[0].size();

    if (N_ <= 2) throw std::invalid_argument("N <= 2 not yet supported.");
    if (N_ != distance.size()) throw std::invalid_argument("Matrix must be square (n x n)");
    if (start < 0 || start >= N_) throw std::invalid_argument("Invalid start node.");
    if (N_ > 32)
      throw std::invalid_argument(
          "Matrix too large! A matrix that size for the DP TSP problem with a time complexity of O(n^2*2^n) requires way too much computation for any modern home computer to handle");

    start_ = start;
    distance_ = distance;
  }


  // Returns the optimal tour for the traveling salesman problem.
  const std::list<int>& getTour() {
    if (!ranSolver_) solve();
    return tour_;
  }


  // Returns the minimal tour cost.
  double getTourCost() {
    if (!ranSolver_) solve();
    return minTourCost_;
  }

};


// Example usage of TSP Dynamic Programming
int TspDynProgIter_test()
{
  // Create adjacency matrix
  int n = 6;
  std::vector<std::vector<double>> distanceMatrix(n, std::vector<double> (n, 10000));
  distanceMatrix[5][0] = 10;
  distanceMatrix[1][5] = 12;
  distanceMatrix[4][1] = 2;
  distanceMatrix[2][4] = 4;
  distanceMatrix[3][2] = 6;
  distanceMatrix[0][3] = 8;

  int startNode = 0;

  try  { 
    std::unique_ptr<TspDynamicProgrammingIterative> solver = std::make_unique<TspDynamicProgrammingIterative>(startNode, distanceMatrix);

    // Prints: [0, 3, 2, 4, 1, 5, 0]
    std::stringstream str;
    str << "Tour: [";
    for (auto node: solver->getTour()) {
      str << "-> ";
      str << node;
    }
    str << "]";
    std::cout << str.str() << std::endl;

    // Print: 42.0
    std::cout << "Tour cost: " << solver->getTourCost() << std::endl;

    solver = nullptr;
  } 
  catch (const std::invalid_argument& ia) {
    std::cerr << "Invalid argument: " << ia.what() << '\n';
  }
  catch (...)  { 
    std::cout << "Default Exception\n"; 
  }
  return 0;
}

} // namespace dsa

#endif /* D_GRAPH_TSPDYNAMICPROGITER_H */
