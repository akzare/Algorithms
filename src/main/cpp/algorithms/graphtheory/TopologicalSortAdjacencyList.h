/*
 * @file   TopologicalSortAdjacencyList.h
 * @author @author William Fiset, william.alexandre.fiset@gmail.com
 *                 Converted from JAVA to C++ by:
 *                 Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   10 July 2020
 * @version 0.1
 * @brief   An implementation of a topological sort
 * This topological sort implementation takes an adjacency list of an acyclic graph and returns an
 * array with the indexes of the nodes in a (non unique) topological order which tells you how to
 * process the nodes in the graph. More precisely from wiki: A topological ordering is a linear
 * ordering of its vertices such that for every directed edge uv from vertex u to vertex v, u comes
 * before v in the ordering.
 *
 * Time Complexity: O(V + E)
 *
 * # Assumption: graph is stored at adjacency list
 * function topsort(graph):
 *
 *   N = graph.numberOfNodes()
 *   V = [false, ...., false] # Length N
 *   Ordering = [0, .., 0] # Length N
 *   i = N - 1 # Index for ordering array
 *
 *   for (at = 0; at < N; at++):
 *     if V[at] == false:
 *       visitedNodes = []
 *       dfs(at, V, visitedNodes, graph)
 *       for nodeId in visitedNodes:
 *         ordering[i] = nodeId
 *         i = i - 1
 *   return ordering
 *
 * # Execute Depth First Search (DFS)
 * function dfs(at, V, visitedNodes, graph):
 *   V[at] = true
 *
 *   edges = graph.getEdgesOutFromNode(at)
 *   for edge in edges:
 *     if V[edge.to] == false:
 *       dfs(edge.to, V, visitedNodes, graph)
 *
 *   visitedNodes.add(at)
 */


#ifndef D_GRAPH_TOPOLOGICALSORT_H
#define D_GRAPH_TOPOLOGICALSORT_H

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

class TopologicalSortAdjacencyList
{

private:
  Graph *graph_;
  unsigned n_;

public:
  TopologicalSortAdjacencyList(Graph *graph) {
    if (graph == nullptr) throw std::invalid_argument("GRAPH NULL");
	n_ = graph->size();
    graph_ = graph;
  }

  TopologicalSortAdjacencyList(const TopologicalSortAdjacencyList&) = delete;
  TopologicalSortAdjacencyList& operator=(TopologicalSortAdjacencyList const&) = delete;

  const Graph& operator()() {
    return *graph_;
  }

private:

  // Perform a depth first search on a graph with n nodes
  // from a starting point to count the number of nodes
  // in a given component.

  // Helper method that performs a depth first search on the graph to give
  // us the topological ordering we want. Instead of maintaining a stack
  // of the nodes we see we simply place them inside the ordering array
  // in reverse order for simplicity.
  int dfs(int i, int at, std::vector<bool>& visited, std::vector<int>& ordering) {

    visited.at(at) = true;

    auto graphItr = (*graph_)()->find(at);
    if (graphItr != (*graph_)()->end()) {
      if (!graphItr->second.empty()){
        for (auto edge: graphItr->second){
          if (!visited[edge.first]) i = dfs(i, edge.first, visited, ordering);
        }
      }
    }

    ordering[i] = at;
    return i - 1;
  }


public:
  // Finds a topological ordering of the nodes in a Directed Acyclic Graph (DAG)
  // The input to this function is an adjacency list for a graph and the number
  // of nodes in the graph.
  //
  std::vector<int> topologicalSort() {

    std::vector<int> ordering(n_, 0);
    std::vector<bool> visited(n_, false);

    int i = n_ - 1;
    for (unsigned at = 0; at < n_; at++)
      if (!visited[at]) i = dfs(i, at, visited, ordering);

    return ordering;
  }


  // A useful application of the topological sort is to find the shortest path
  // between two nodes in a Directed Acyclic Graph (DAG). Given an adjacency list
  // this method finds the shortest path to all nodes starting at 'start'
  //
  std::vector<int> dagShortestPath(int start) {
    std::vector<int> dist(n_, -1);
	if (n_ == 0) return dist;

	if (start < 0 || (unsigned)start >= n_) throw std::invalid_argument("Invalid start node index");

    std::vector<int> topsort = topologicalSort();

    dist[start] = 0;

    for (unsigned i = 0; i < n_; i++) {

      int nodeIndex = topsort[i];
      if (dist[nodeIndex] != -1) {

        auto adjacentEdges = (*graph_)()->find(nodeIndex);
        if (adjacentEdges != (*graph_)()->end()) {
          if (!adjacentEdges->second.empty()) {
            for (auto edge: adjacentEdges->second) {
              int newDist = dist[nodeIndex] + static_cast<int>(edge.second);
              if (dist[edge.first] == -1) dist[edge.first] = newDist;
              else dist[edge.first] = std::min(dist[edge.first], newDist);
            }
          }
        }
      }
    }

    return dist;
  }

};



// Example usage of TopologicalSort
int topologicalSort_test()
{
  Graph graph(7);

  graph.addDirectedEdge(0, 1, 3.);
  graph.addDirectedEdge(0, 2, 2.);
  graph.addDirectedEdge(0, 5, 3.);
  graph.addDirectedEdge(1, 3, 1.);
  graph.addDirectedEdge(1, 2, 6.);
  graph.addDirectedEdge(2, 3, 1.);
  graph.addDirectedEdge(2, 4, 10.);
  graph.addDirectedEdge(3, 4, 5.);
  graph.addDirectedEdge(5, 4, 7.);

  TopologicalSortAdjacencyList solver(&graph);

  std::vector<int> ordering = solver.topologicalSort();

  // Prints: [6, 0, 5, 1, 2, 3, 4]
  {
  std::stringstream ss;
  for (auto node: ordering) {
    ss << "-> ";
    ss << node;
  }
  std::string s = ss.str();
  std::cout << "Ordering :" << s << std::endl;
  }

  // Finds all the shortest paths starting at node 0
  std::vector<int> dists = solver.dagShortestPath(0);

  // Find the shortest path from 0 to 4 which is 8.0
  std::cout << "Find the shortest path from 0 to 4: " << dists[4] << std::endl;

  // Find the shortest path from 0 to 6 which
  // is null since 6 is not reachable!
  std::cout << "Find the shortest path from 0 to 6: " << dists[6] << std::endl;

  return 0;
}

} // namespace dsa

#endif /* D_GRAPH_TOPOLOGICALSORT_H */
