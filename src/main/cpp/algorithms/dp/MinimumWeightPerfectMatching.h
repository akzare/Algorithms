/*
 * @file   MinimumWeightPerfectMatching.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   14 July 2020
 * @version 0.1
 * @brief   Implementation of the Minimum Weight Perfect Matching (MWPM) problem. In this problem you are
 * given a distance matrix which gives the distance from each node to every other node, and you want
 * to pair up all the nodes to one another minimizing the overall cost.
 *
 * <p>Time Complexity: O(n^2 * 2^n)
 */

#ifndef D_MINWEIGHTPERFECTMATCHING_H
#define D_MINWEIGHTPERFECTMATCHING_H

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
#include <random>

namespace dsa {


// Base class Point2D represents a point in two dimensional space
class Point2D {

public:
  // Overloaded constructor with zero parameters
  Point2D() : x_(0.0), y_(0.0) {}

  // Overloaded constructor with two parameters
  Point2D(double x2, double y2) : x_(x2), y_(y2) {}

  // set (mutator) functions
  void setX(double x2) { x_ = x2; }
  void setY(double y2) { y_ = y2; }

  // get (accessor) functions
  double getX() { return x_; }
  double getY(){ return y_; }

  // Returns the distance from point (0,0).
  // Can be the magnitude of a vector or length of a line.
  double distance() { return sqrt(x_*x_ + y_*y_); }
  double distance(Point2D pt) { return sqrt(x_*pt.x_ + y_*pt.y_); }

  //friend function for overloading output operator<<()
  friend std::ostream & operator << (std::ostream & output, const Point2D & point) {
    output << "(" << point.x_ << ", " << point.y_ << ")";
    return output;
  }

  //data members represent two points in space
protected:
  double x_;
  double y_;
};



class MinimumWeightPerfectMatching {
private:
  // Inputs
  int n_;
  std::vector<std::vector<double>> cost_;

  // Internal
  bool solved_;

  // Outputs
  double minWeightCost_;
  std::vector<int> matching_;

public:
  // The cost matrix should be a symmetric (i.e cost[i][j] = cost[j][i])
  MinimumWeightPerfectMatching(const std::vector<std::vector<double>>& cost) {
    if (cost.size() == 0) throw std::invalid_argument("Input cannot be null");
    n_ = cost.size();
    if (n_ == 0) throw std::invalid_argument("Matrix size is zero");
    if (n_ % 2 != 0)
      throw std::invalid_argument("Matrix has an odd size, no perfect matching exists.");
    if (n_ > 32)
      throw std::invalid_argument(
          std::string("Matrix too large! A matrix that size for the MWPM problem with a time complexity of")
              + std::string("O(n^2*2^n) requires way too much computation and memory for a modern home computer."));
    cost_ = cost;
    minWeightCost_ = 0;
    solved_ = false;
  }


  double getMinWeightCost() {
    solve();
    return minWeightCost_;
  }

  /**
   * Get the minimum weight cost matching. The matching is returned as an array where the nodes at
   * index 2*i and 2*i+1 form a matched pair. For example, nodes at indexes (0, 1) are a pair, (2,
   * 3) are another pair, etc...
   *
   * <p>How to iterate over the pairs:
   *
   * <pre>{@code
   * MinimumWeightPerfectMatching mwpm = ...
   * int[] matching = mwpm.getMinWeightCostMatching();
   * for (int i = 0; i < matching.length / 2; i++) {
   *   int node1 = matching[2*i];
   *   int node2 = matching[2*i+1];
   *   // Do something with the matched pair (node1, node2)
   * }
   * }</pre>
   */
  std::vector<int> getMinWeightCostMatching() {
    solve();
    return matching_;
  }

  void solve() {
    if (solved_) return;

    int END_STATE = (1 << n_) - 1;
//    std::cout << "n=" << n_ << " end state:" << std::hex << END_STATE << std::dec << std::endl;

    // The DP state is encoded as a bitmask where the i'th bit is flipped on if the i'th node is
    // included in the state. Encoding the state this way allows us to compactly represent selecting
    // a subset of the nodes present in the matching. Furthermore, it allows using the '&' binary
    // operator to compare states to see if they overlap and the '|' operator to combine states.
    std::vector<double> dp(1 << n_, 0);

    // Memo table to save the history of the chosen states. This table is used to reconstruct the
    // chosen pairs of nodes after the algorithm has executed.
    std::vector<int> history(1 << n_, 0);

    // Singleton pair states with only two nodes are the building blocks of this algorithm. Every
    // iteration, we try to add singleton pairs to previous states to construct a larger matching.
    int numPairs = (n_ * (n_ + 1)) / 2;
    std::vector<int> pairStates(numPairs, 0);
    std::vector<double> pairCost(numPairs, 0);

    for (int i = 0, k = 0; i < n_; i++) {
      for (int j = i + 1; j < n_; j++, k++) {
        int state = (1 << i) | (1 << j);
        dp[state] = cost_[i][j];
        pairStates[k] = state;
        pairCost[k] = cost_[i][j];
      }
    }

//    std::cout << "Before dp: [";
//    for (int i=0; i<100; i++) std::cout << dp[i] << " ";
////    for (auto d : dp) std::cout << d << " ";
//    std::cout << "]" << std::endl;

    for (int state = 0; state < (1 << n_); state++) {
      // A cost of null means the previous state does not exist.
      if (dp[state] == 0) continue;
      for (int i = 0; i < numPairs; i++) {
        int pair = pairStates[i];
        // Ignore states which overlap
        if ((state & pair) != 0) continue;

        int newState = state | pair;
        double newCost = dp[state] + pairCost[i];
//        if (newState == END_STATE) std::cout << "dp[" << newState << "]:" << dp[newState] << " NewCost:"<< newCost << std::endl;
        if (dp[newState] == 0 || newCost < dp[newState]) {
          dp[newState] = newCost;
          // Save the fact that we went from 'state' -> 'newState'. From this we will be able to
          // reconstruct which pairs of nodes were taken by looking at 'state' xor 'newState' which
          // should give us the binary representation (state) of the pair used.
          history[newState] = state;
          if (newState == END_STATE) std::cout << "dp[" << newState << "]:" << dp[newState] << std::endl;
        }
      }
    }

//    std::cout << "After dp: [";
//    for (int i=0; i<100; i++) std::cout << dp[i] << " ";
////    for (auto d : dp) std::cout << d << " ";
//    std::cout << "]" << std::endl;

    // Reconstruct the matching of pairs of nodes.
    matching_ = std::vector<int>(n_);
    for (int i = 0, state = END_STATE; state != 0; state = history[state]) {
      int pairUsed = state ^ history[state];
      matching_[i++] = getBitPosition(lowestOneBit(pairUsed));
      matching_[i++] = getBitPosition(highestOneBit(pairUsed));
    }

    minWeightCost_ = dp[END_STATE];
    solved_ = true;
  }


private:
  // The lowestOneBit returns an int value with at most a single one-bit,
  // in the position of the lowest-order one-bit in the specified int value.
  static int lowestOneBit(int i) {
    return i & -i;
  }


  static int highestOneBit(int i) {
    i |= (i >>  1);
    i |= (i >>  2);
    i |= (i >>  4);
    i |= (i >>  8);
    i |= (i >> 16);
    return i - (((unsigned)i) >> 1);
  }


  // Gets the zero base index position of the 1 bit in 'k'
  int getBitPosition(int k) {
    int count = -1;
    while (k > 0) {
      count++;
      k >>= 1;
    }
    return count;
  }

};


void MinimumWeightPerfectMatching_test()
{
  int n = 18;
  std::vector<Point2D> pts;

  // Generate points on a 2D plane which will produce a unique answer
  for (int i = 0; i < n / 2; i++) {
    pts.push_back(Point2D(2 * i, 0));
    pts.push_back(Point2D(2 * i, 1));
  }
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(pts.begin(), pts.end(), g);

  std::vector<std::vector<double>> cost(n, std::vector<double>(n, 0.0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cost[i][j] = pts[i].distance(pts[j]);
//      std::cout << cost[i][j] << std::endl;
    }
  }

  MinimumWeightPerfectMatching mwpm = MinimumWeightPerfectMatching(cost);
  double minCost = mwpm.getMinWeightCost();
  if (minCost != n / 2) {
    std::cout << "MWPM cost is wrong! Got: " << minCost << " But wanted: " << n / 2 << std::endl;
  } else {
    std::cout << "MWPM is: " << minCost << std::endl;
  }

  std::vector<int> matching = mwpm.getMinWeightCostMatching();
  for (unsigned i = 0; i < matching.size() / 2; i++) {
    int ii = matching[2 * i];
    int jj = matching[2 * i + 1];
    std::cout <<
        "(" << (int) pts[ii].getX() << ", " << (int) pts[ii].getY() << ") <-> (" << (int) pts[jj].getX() << ", " << (int) pts[jj].getY() << ")" << std::endl;
  }
}

} // namespace dsa

#endif /* D_MINWEIGHTPERFECTMATCHING_H */
