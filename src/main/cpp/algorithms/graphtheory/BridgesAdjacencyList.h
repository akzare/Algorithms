/*
 * @file   BridgesAdjacencyList.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   11 July 2020
 * @version 0.1
 * @brief   Finds all the bridges on an undirected graph.
 *
 * <p>Test against HackerEarth online judge at:
 * https://www.hackerearth.com/practice/algorithms/graphs/articulation-points-and-bridges/tutorial
 *
 * id = 0
 * g = adjacency list with undirected edges
 * n = size of the graph
 *
 * # In these arrays index i represents node i
 * ids = [0, 0, ..., 0, 0] # Length n
 * low = [0, 0, ..., 0, 0] # Length n
 * visisted = [false, ..., false] # Length n
 *
 * function findBridges():
 *   bridges = []
 *   # Finds all bridges in the graph across
 *   # various connected components
 *   for (i = 0; i < n; i = i + 1):
 *     if (!visisted[i]):
 *       dfs(i, -1, bridges)
 *   return bridges
 *
 * # Performe Depth First Search (DFS) to find bridges.
 * # at = current node, parent = previous node. The
 * # bridges list is always of even length and indexes
 * # (2*i, 2*i+1) from a bridge. For example, nodes at
 * # indexes (0, 1) are a bridge, (2, 3) is another etc.
 * function dfs (at, parent, bridges):
 *   visited[at] = true
 *   id = id + 1
 *   low[at] = id[at] = id
 *
 *   # For each edge from node 'at' to node 'to'
 *   for (to : g[at]):
 *     if to == parent: continue
 *     if (!visited[to]):
 *       dfs(to, at, bridges)
 *       low[at] = min(low[at], low[to])
 *       if (ids[at] low[to]):
 *         bridges.add(at)
 *         bridges.add(to)
 *     else:
 *       low[at] = min(low[at], ids[to])
 */

#ifndef D_GRAPH_BRIDGES_H
#define D_GRAPH_BRIDGES_H

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
#include <stdexcept>

namespace dsa {

class BridgesAdjacencyList {
private:
  const double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
  const double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();

  int N_, id_;
  std::vector<int> low_, ids_;
  bool solved_;
  std::vector<bool> visited_;
  Graph *graph_;
  std::vector<int> bridges_;


  void dfs(int at, int parent) {

    visited_[at] = true;
    low_[at] = ids_[at] = ++id_;

    auto graphItr = (*graph_)()->find(at);
    if (graphItr != (*graph_)()->end()) {
      if (!graphItr->second.empty()){
        for (auto edge: graphItr->second){
          if (edge.first == parent) continue;
          if (!visited_[edge.first]) {
            dfs(edge.first, at);
            low_[at] = std::min(low_[at], low_[edge.first]);
            if (ids_[at] < low_[edge.first]) {
              bridges_.push_back(at);
              bridges_.push_back(edge.first);
            }
          } else {
            low_[at] = std::min(low_[at], ids_[edge.first]);
          }
        }
      }
    }

  }

public:
  BridgesAdjacencyList(const BridgesAdjacencyList&) = delete;
  BridgesAdjacencyList& operator=(BridgesAdjacencyList const&) = delete;
  
  BridgesAdjacencyList(Graph *graph) {
	if (graph == nullptr) throw std::invalid_argument("GRAPH NULL");
    N_ = graph->size();
    if (N_ == 0) throw std::invalid_argument("GRAPH Empty");
    graph_ = graph;

    id_ = 0;
    low_.resize(N_, -1); // Low link values
    ids_.resize(N_, 0); // Nodes ids
    visited_.resize(N_, false);
    solved_ = false;
  }



  // Returns a list of pairs of nodes indicating which nodes form bridges.
  // The returned list is always of even length and indexes (2*i, 2*i+1) form a
  // pair. For example, nodes at indexes (0, 1) are a pair, (2, 3) are another
  // pair, etc...
  const std::vector<int>& findBridges() {
    if (solved_) return bridges_;

    // Finds all bridges in the graph across various connected components.
    for (int i = 0; i < N_; i++) if (!visited_[i]) dfs(i, -1);

    solved_ = true;
    return bridges_;
  }

};



// Example usage of Bridge
int Bridge_test()
{
  Graph graph(9);

  graph.addUndirectedEdge(0, 1);
  graph.addUndirectedEdge(0, 2);
  graph.addUndirectedEdge(1, 2);
  graph.addUndirectedEdge(2, 3);
  graph.addUndirectedEdge(3, 4);
  graph.addUndirectedEdge(2, 5);
  graph.addUndirectedEdge(5, 6);
  graph.addUndirectedEdge(6, 7);
  graph.addUndirectedEdge(7, 8);
  graph.addUndirectedEdge(8, 5);

  try  {

    std::unique_ptr<BridgesAdjacencyList> solver = std::make_unique<BridgesAdjacencyList>(&graph);

    std::vector<int> bridges = solver->findBridges();

    // Prints:
    // Bridge between nodes: 3 and 4
    // Bridge between nodes: 2 and 3
    // Bridge between nodes: 2 and 5
    int from = -1;
    for (auto b: bridges) {
      if (from == -1) from = b;
      else {
        std::cout << "Bridge between nodes: " << from << " and " << b << std::endl;
        from = -1;
      }
    }

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

#endif /* D_GRAPH_BRIDGES_H */
