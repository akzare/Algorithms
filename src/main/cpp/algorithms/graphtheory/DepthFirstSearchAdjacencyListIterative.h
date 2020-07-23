/*
 * @file   DepthFirstSearchAdjacencyListIterative.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   09 July 2020
 * @version 0.1
 * @brief   An implementation of a iterative DFS with an adjacency list
 *          Time Complexity: O(V + E)
 *
 * # Global or class scope variables
 * n = number of nodes in the graph
 * g = adjacency list representing graph
 * visited = [false, ..., false] # size n
 *
 * function dfs(at):
 *   if visited[at]: return
 *   visited[at] = true
 *
 *   neighbours = graph[at]
 *   for next in neighbours:
 *     dfs(next)
 *
 * # Start DFS at node zero
 * start_node = 0
 * dfs(start_node)
 */

#ifndef D_GRAPH_DEPTHFIRSTSEARCH_H
#define D_GRAPH_DEPTHFIRSTSEARCH_H

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

#include <iostream>

namespace dsa {

class DepthFirstSearchAdjacencyListIterative
{

private:
  Graph *graph_;
  unsigned n_;

public:
  DepthFirstSearchAdjacencyListIterative(Graph *graph) {
    if (graph == nullptr) throw std::invalid_argument("GRAPH NULL");
	n_ = graph->size();
    graph_ = graph;
  }

  DepthFirstSearchAdjacencyListIterative(const DepthFirstSearchAdjacencyListIterative&) = delete;
  DepthFirstSearchAdjacencyListIterative& operator=(DepthFirstSearchAdjacencyListIterative const&) = delete;

  const Graph& operator()() {
    return *graph_;
  }

public:

  // Perform a depth first search on a graph with n nodes
  // from a starting point to count the number of nodes
  // in a given component.
  int dfs(int start) {
    int count = 0;

    if (n_ == 0) return count;

    if (start < 0 || (unsigned)start >= n_) throw std::invalid_argument("Invalid start node index");

    std::vector<bool> visited(n_, false);
    std::stack<int> stack_;

    std::cout  << std::endl;

    // Start by visiting the starting node
    stack_.push(start);

    while (!stack_.empty()) {
      int node = stack_.top();
      stack_.pop();
      if (!visited[node]) {
        count++;
        visited[node] = true;
        std::cout << "DFS visiting node: " <<  node << std::endl;
        auto graphItr = (*graph_)()->find(node);
        if (graphItr != (*graph_)()->end()) {
          std::cout << "  is in graph map" <<  std::endl;
          if (!graphItr->second.empty()){
            for (auto edge: graphItr->second){
              if (!visited[edge.first]) {
                stack_.push(edge.first);
                std::cout << "    visiting edge: " <<  graphItr->first << " -> " << edge.first << std::endl;
              }
              else{
                std::cout << "    already visited edge: " <<  graphItr->first << " -> " << edge.first << std::endl;
              }
            }
          }
        }
        else {
          std::cout << "  is not in graph map" <<  std::endl;
        }
      }
    }

    std::cout  << std::endl;

    return count;
  }
};



// Example usage of DFS
int dfs_test()
{
  // Create a fully connected graph
  //           (0)
  //           / \
  //        5 /   \ 4
  //         /     \
  // 10     <   -2  >
  //   +->(2)<------(1)      (4)
  //   +--- \       /
  //         \     /
  //        1 \   / 6
  //           > <
  //           (3)
  Graph graph(5);

  graph.addDirectedEdge(0, 1);
  graph.addDirectedEdge(0, 2);
  graph.addDirectedEdge(1, 2);
  graph.addDirectedEdge(1, 3);
  graph.addDirectedEdge(2, 3);
  graph.addDirectedEdge(2, 2); // Self loop

  DepthFirstSearchAdjacencyListIterative solver(&graph);

  int nodeCount = solver.dfs(0);
  std::cout << "DFS node count starting at node 0: " <<  nodeCount << std::endl;
  if (nodeCount != 4) std::cout << "Error with DFS " << std::endl;

  nodeCount = solver.dfs(4);
  std::cout << "DFS node count starting at node 4:" <<  nodeCount << std::endl;
  if (nodeCount != 1) std::cout << "Error with DFS" << std::endl;

  return 0;
}

} // namespace dsa

#endif /* D_GRAPH_DEPTHFIRSTSEARCH_H */
