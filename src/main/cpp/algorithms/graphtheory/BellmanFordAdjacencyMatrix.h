/*
 * @file   BellmanFordAdjacencyMatrix.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   10 July 2020
 * @version 0.1
 * @brief
 * An implementation of the Bellman-Ford algorithm. The algorithm finds the shortest path between a
 * starting node and all other nodes in the graph. The algorithm also detects negative cycles.
 */
#ifndef D_GRAPH_BELLMANFORDADJMATRIX_H
#define D_GRAPH_BELLMANFORDADJMATRIX_H


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

class BellmanFordAdjacencyMatrix {

private:
  const double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
  const double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();

  int n_, start_;
  bool solved_;
  std::vector<double> dist_;
  std::vector<int> prev_;
  std::vector<std::vector<double>> *matrix_;

public:
  BellmanFordAdjacencyMatrix(const BellmanFordAdjacencyMatrix&) = delete;
  BellmanFordAdjacencyMatrix& operator=(BellmanFordAdjacencyMatrix const&) = delete;

  // An implementation of the Bellman-Ford algorithm. The algorithm finds the shortest path between
  // a starting node and all other nodes in the graph. The algorithm also detects negative cycles.
  // If a node is part of a negative cycle then the minimum cost for that node is set to
  // Double.NEGATIVE_INFINITY.
  //
  // @param graph - An adjacency matrix containing directed edges forming the graph
  // @param start - The id of the starting node
  //
  BellmanFordAdjacencyMatrix(int start, std::vector<std::vector<double>> *matrix) {
    n_ = matrix->size();
    start_ = start;
    matrix_ = matrix;
    solved_ = false;
  }

  std::vector<double>& getShortestPaths() {
    if (!solved_) solve();
    return dist_;
  }

  void reconstructShortestPath(int end, std::list<int> &path) {
    if (!solved_) solve();
    path.clear();
    if (dist_[end] == POSITIVE_INFINITY) return;
    for (int at = end; prev_[at] != -1; at = prev_[at]) {
      // Return null since there are an infinite number of shortest paths.
      if (prev_[at] == -1) { path.clear(); return; }
      path.push_front(at);
    }
    path.push_front(start_);
    return;
  }

  void solve() {
    if (solved_) return;

    // Initialize the distance to all nodes to be infinity
    // except for the start node which is zero.
    dist_ = std::vector<double> (n_, POSITIVE_INFINITY);
    dist_[start_] = 0;

    // Initialize prev array which will allows for shortest path
    // reconstruction after the algorithm has terminated.
    prev_ = std::vector<int> (n_, -1);

    // For each vertex, apply relaxation for all the edges
    for (int k = 0; k < n_ - 1; k++)
      for (int i = 0; i < n_; i++)
        for (int j = 0; j < n_; j++)
          if (dist_[i] + (*matrix_)[i][j] < dist_[j]) {
            dist_[j] = dist_[i] + (*matrix_)[i][j];
            prev_[j] = i;
          }

    // Run algorithm a second time to detect which nodes are part
    // of a negative cycle. A negative cycle has occurred if we
    // can find a better path beyond the optimal solution.
    for (int k = 0; k < n_ - 1; k++)
      for (int i = 0; i < n_; i++)
        for (int j = 0; j < n_; j++)
          if (dist_[i] + (*matrix_)[i][j] < dist_[j]) {
            dist_[j] = NEGATIVE_INFINITY;
            prev_[j] = -1;
          }

    solved_ = true;
  }

};


// Example usage of BellmanFord
int BellmanFordMatrix_test()
{
  int n = 9;
  std::vector<std::vector<double>> graph = std::vector<std::vector<double>>(n, std::vector<double> (n, std::numeric_limits<double>::infinity()));

  // Setup completely disconnected graph with the distance
  // from a node to itself to be zero.
  for (int i = 0; i < n; i++) {
    graph[i][i] = 0;
  }

  graph[0][1] = 1;
  graph[1][2] = 1;
  graph[2][4] = 1;
  graph[4][3] = -3;
  graph[3][2] = 1;
  graph[1][5] = 4;
  graph[1][6] = 4;
  graph[5][6] = 5;
  graph[6][7] = 4;
  graph[5][7] = 3;

  int start = 0;
  std::unique_ptr<BellmanFordAdjacencyMatrix> solver = std::make_unique<BellmanFordAdjacencyMatrix>(start, &graph);
  std::vector<double> d = solver->getShortestPaths();

  for (int i = 0; i < n; i++)
    std::cout << "The cost to get from node " << start << " to " << i << " is " << d[i] << std::endl;

  // Output:
  // The cost to get from node 0 to 0 is 0.00
  // The cost to get from node 0 to 1 is 1.00
  // The cost to get from node 0 to 2 is -Infinity
  // The cost to get from node 0 to 3 is -Infinity
  // The cost to get from node 0 to 4 is -Infinity
  // The cost to get from node 0 to 5 is 5.00
  // The cost to get from node 0 to 6 is 5.00
  // The cost to get from node 0 to 7 is 8.00
  // The cost to get from node 0 to 8 is Infinity
  std::cout << std::endl;

  for (int i = 0; i < n; i++) {
	std::stringstream strPath;
    std::list<int> path;
    solver->reconstructShortestPath(i, path);
    if (path.size() == 0) {
      strPath << "Infinite number of shortest paths.";
    } else {
      strPath << "[";
      for (auto node: path) {
    	strPath << " -> ";
    	strPath << node;
      }
      strPath << "]";
    }
    std::cout << "The shortest path from " << start << " to " << i << " is: " << strPath.str() << std::endl;
  }
  // Outputs:
  // The shortest path from 0 to 0 is: [0]
  // The shortest path from 0 to 1 is: [0 -> 1]
  // The shortest path from 0 to 2 is: [Infinite number of shortest paths.]
  // The shortest path from 0 to 3 is: [Infinite number of shortest paths.]
  // The shortest path from 0 to 4 is: [Infinite number of shortest paths.]
  // The shortest path from 0 to 5 is: [0 -> 1 -> 5]
  // The shortest path from 0 to 6 is: [0 -> 1 -> 6]
  // The shortest path from 0 to 7 is: [0 -> 1 -> 5 -> 7]
  // The shortest path from 0 to 8 is: []

  solver = nullptr;
  return 0;
}


} // namespace dsa

#endif /* D_GRAPH_BELLMANFORDADJMATRIX_H */
