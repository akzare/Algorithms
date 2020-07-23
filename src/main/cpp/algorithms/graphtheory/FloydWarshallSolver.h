/*
 * @file   FloydWarshallSolver.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   10 July 2020
 * @version 0.1
 * @brief   An implementation of the Floyd-Warshall algorithm
 * This file contains an implementation of the Floyd-Warshall algorithm to find all pairs of
 * shortest paths between nodes in a graph. We also demonstrate how to detect negative cycles and
 * reconstruct the shortest path.
 *
 * Time Complexity: O(V^3)
 *
 * # Global/class scope variables
 * n = size of the adjacency matrix
 * dp = the memo table that will contain APSP solution
 * next = matrix used to reconstruct shortest paths
 *
 * function floydWarshall(m):
 *   setup(m)
 *
 *   # Execute FW all pairs shortest path algorithm.
 *   for (k:=0; k<n; k++):
 *     for (i:=0; i<n; i++):
 *       for (j:=0; j<n; j++):
 *         if (dp[i][k] + dp[k][j] < dp[i][j]):
 *           dp[i][j] = dp[i][k] + dp[k][j]
 *           next[i][j] = next[i][k]
 *   # Detect and propagate negative cycles.
 *   propagateNegativeCycles(dp, n)
 *
 *   # Return APSP matrix
 *   return dp
 *
 * function setup(m):
 *   dp = empty matrix of size n x n
 *
 *   # Should contain null values by defualt
 *   next = empty integer matrix of size n x n
 *
 *   # Do a deep copy of the input matrix and set
 *   # the next matrix for path reconstruction.
 *   for (i:=0; i<n; i++):
 *     for (j:=0; j<n; j++):
 *       dp[i][j] = m[i][j]
 *       if m[i][j] != +inf:
 *         next[i][j] = j
 *
 *
 * function propagateNegativeCycles(dp, n):
 *
 *   # Execute FW APSP algorithm a second time but
 *   # this time if the distance can be improved
 *   # set the optimal distance to be -inf.
 *   # Every edge (i, j) marked with -inf is either
 *   # part of or reaches into a negative cycle.
 *   for (k:=0; k<n; k++):
 *     for (i:=0; i<n; i++):
 *       for (j:=0; j<n; j++):
 *         if (dp[i][k] + dp[k][j] < dp[i][j]):
 *           dp[i][j] = -inf
 *           next[i][j] = -1
 *
 * # Reconstruct the shortest path between nodes
 * # start and end. You must run the
 * # floydWarshall solver before calling this method.
 * # Returns null if path is affected by negative cycle.
 * function reconstructPath(start, end):
 *   path = []
 *   # Check if there exists a path between
 *   # the start and the end node.
 *   if dp[start][end] == +inf: return path
 *
 *   at := start
 *   # Reconstruct path from next matrix
 *   for (; at!=end; at=next[at][end]):
 *     if at == -1: return null
 *     path.add(at)
 *
 *   if next[at][end] == -1: return null
 *   path.add(end)
 *   return path
 *
 */
#ifndef D_GRAPH_FLOYDWARSHALL_H
#define D_GRAPH_FLOYDWARSHALL_H

#include <Graph.h>

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

namespace dsa {

class FloydWarshallSolver
{
  const int REACHES_NEGATIVE_CYCLE = -1;
  const double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
  const double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();
  int n_;
  bool solved_;
  std::vector<std::vector<double>> dp_;
  std::vector<std::vector<int>> next_;

public:
  FloydWarshallSolver(const FloydWarshallSolver&) = delete;
  FloydWarshallSolver& operator=(FloydWarshallSolver const&) = delete;


  // As input, this class takes an adjacency matrix with edge weights between nodes, where
  // POSITIVE_INFINITY (inf) is used to indicate that two nodes are not connected.
  //
  // NOTE: Usually the diagonal of the adjacency matrix is all zeros (i.e. matrix[i][i] = 0 for
  // all i) since there is typically no cost to go from a node to itself, but this may depend on
  // your graph and the problem you are trying to solve.
  //
  FloydWarshallSolver(std::vector<std::vector<double> > matrix) {
    n_ = matrix[0].size();
    dp_.resize(n_, std::vector<double>(n_));
    next_.resize(n_, std::vector<int>(n_));

    // Copy input matrix and setup 'next' matrix for path reconstruction.
    for (int i = 0; i < n_; i++) {
      for (int j = 0; j < n_; j++) {
        if (matrix[i][j] != POSITIVE_INFINITY) next_[i][j] = j;
        dp_[i][j] = matrix[i][j];
      }
    }
    solved_ = false;
  }


  // Runs Floyd-Warshall to compute the shortest distance between every pair of nodes.
  //
  // @return The solved All Pairs Shortest Path (APSP) matrix.
  //
  std::vector<std::vector<double>>& getApspMatrix() {
    solve();
    return dp_;
  }


  // Executes the Floyd-Warshall algorithm.
  void solve() {
    if (solved_) return;

    // Compute all pairs shortest paths.
    for (int k = 0; k < n_; k++) {
      for (int i = 0; i < n_; i++) {
        for (int j = 0; j < n_; j++) {
          if (dp_[i][k] + dp_[k][j] < dp_[i][j]) {
            dp_[i][j] = dp_[i][k] + dp_[k][j];
            next_[i][j] = next_[i][k];
          }
        }
      }
    }

    // Identify negative cycles by propagating the value 'NEGATIVE_INFINITY'
    // to every edge that is part of or reaches into a negative cycle.
    for (int k = 0; k < n_; k++)
      for (int i = 0; i < n_; i++)
        for (int j = 0; j < n_; j++)
          if (dp_[i][k] + dp_[k][j] < dp_[i][j]) {
            dp_[i][j] = NEGATIVE_INFINITY;
            next_[i][j] = REACHES_NEGATIVE_CYCLE;
          }

    solved_ = true;
  }


  // Reconstructs the shortest path (of nodes) from 'start' to 'end' inclusive.
  //
  // @return An array of nodes indexes of the shortest path from 'start' to 'end'. If 'start' and
  //     'end' are not connected return an empty array. If the shortest path from 'start' to 'end'
  //     are reachable by a negative cycle return -1.
  //
  std::tuple <bool, std::list<int>> reconstructShortestPath(int start, int end) {
    solve();
    std::list<int> path;
    if (dp_[start][end] == POSITIVE_INFINITY) return make_tuple(false, path);
    int at = start;
    for (; at != end; at = next_[at][end]) {
      // Return null since there are an infinite number of shortest paths.
      if (at == REACHES_NEGATIVE_CYCLE) return make_tuple(true, path);
      path.push_back(at);
    }
    // Return null since there are an infinite number of shortest paths.
    if (next_[at][end] == REACHES_NEGATIVE_CYCLE) return make_tuple(true, path);
    path.push_back(end);
    return make_tuple(false, path);
  }


  // Creates a graph with n nodes. The adjacency matrix is constructed
  // such that the value of going from a node to itself is 0.
  static void createGraph(int n, std::vector<std::vector<double>>& matrix) {
    //Asserts floating point compatibility at compile time
    static_assert(std::numeric_limits<float>::is_iec559, "IEEE 754 required");
    matrix = std::vector<std::vector<double>>(n , std::vector<double> (n, std::numeric_limits<double>::infinity()));
    for (int i = 0; i < n; i++) {
      matrix[i][i] = 0;
    }
  }

};



// Example usage of Floyd Warshall
int FloydWarshall_test()
{
  // Construct graph.
  int n = 7;
  std::vector<std::vector<double>> m;
  FloydWarshallSolver::createGraph(n, m);

  // Add some edge values.
  m[0][1] = 2;
  m[0][2] = 5;
  m[0][6] = 10;
  m[1][2] = 2;
  m[1][4] = 11;
  m[2][6] = 2;
  m[6][5] = 11;
  m[4][5] = 1;
  m[5][4] = -2;

  std::unique_ptr<FloydWarshallSolver> solver = std::make_unique<FloydWarshallSolver>(m);
  std::vector<std::vector<double>> dist = solver->getApspMatrix();

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      std::cout << "This shortest path from node " << i << " to node " << j << " is " << dist[i][j] << std::endl;

  // Prints:
  // This shortest path from node 0 to node 0 is 0.000
  // This shortest path from node 0 to node 1 is 2.000
  // This shortest path from node 0 to node 2 is 4.000
  // This shortest path from node 0 to node 3 is Infinity
  // This shortest path from node 0 to node 4 is -Infinity
  // This shortest path from node 0 to node 5 is -Infinity
  // This shortest path from node 0 to node 6 is 6.000
  // This shortest path from node 1 to node 0 is Infinity
  // This shortest path from node 1 to node 1 is 0.000
  // This shortest path from node 1 to node 2 is 2.000
  // This shortest path from node 1 to node 3 is Infinity
  // ...


  // Reconstructs the shortest paths from all nodes to every other nodes.
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::list<int> path;
      bool isNegCycle;
      std::tie(isNegCycle, path) = solver->reconstructShortestPath(i, j);
      std::stringstream str;

      if (isNegCycle == true) {
        str << "HAS AN INF NUMBER OF SOLUTIONS! (negative cycle case)";
      } else if (path.size() == 0) {
        str << "DOES NOT EXIST (node " << i << " doesn't reach node " << j << ")";
      } else {
        str << "is: [";
        for (auto node: path) {
          str << "-> ";
          str << node;
        }
        str << "]";
      }

      std::cout << "The shortest path from node " << i << " to node " << j << " " << str.str() << std::endl;
    }
  }

  // Prints:
  // The shortest path from node 0 to node 0 is: [0]
  // The shortest path from node 0 to node 1 is: [0 -> 1]
  // The shortest path from node 0 to node 2 is: [0 -> 1 -> 2]
  // The shortest path from node 0 to node 3 DOES NOT EXIST (node 0 doesn't reach node 3)
  // The shortest path from node 0 to node 4 HAS AN INF NUMBER OF SOLUTIONS! (negative cycle case)
  // The shortest path from node 0 to node 5 HAS AN INF NUMBER OF SOLUTIONS! (negative cycle case)
  // The shortest path from node 0 to node 6 is: [0 -> 1 -> 2 -> 6]
  // The shortest path from node 1 to node 0 DOES NOT EXIST (node 1 doesn't reach node 0)
  // The shortest path from node 1 to node 1 is: [1]
  // The shortest path from node 1 to node 2 is: [1 -> 2]
  // The shortest path from node 1 to node 3 DOES NOT EXIST (node 1 doesn't reach node 3)
  // The shortest path from node 1 to node 4 HAS AN INF NUMBER OF SOLUTIONS! (negative cycle case)
  // The shortest path from node 1 to node 5 HAS AN INF NUMBER OF SOLUTIONS! (negative cycle case)
  // The shortest path from node 1 to node 6 is: [1 -> 2 -> 6]
  // The shortest path from node 2 to node 0 DOES NOT EXIST (node 2 doesn't reach node 0)
  // ...

  solver = nullptr;

  return 0;
}

} // namespace dsa

#endif /* D_GRAPH_FLOYDWARSHALL_H */
