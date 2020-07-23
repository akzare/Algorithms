/*
 * @file   TarjanSccSolverAdjacencyList.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   11 July 2020
 * @version 0.1
 * @brief   An implementation of Tarjan's Strongly Connected Components algorithm using an adjacency list.
 * Time complexity: O(V+E)
 *
 * UNVISITED = -1
 * n = number of nodes in graph
 * g = adjacency list with directed edges
 *
 * id = 0 # Used to give each node an id
 * sccCount = 0 # Used to count number of SCCs found
 *
 * # Index i in these arrays represents node i
 * ids = [0, 0, ..., 0, 0] # Length n
 * low = [0, 0, ..., 0, 0] # Length n
 * onStack = [false, false, ..., false] # Length n
 * stack = an empty stack data structure
 *
 * function findSccs():
 *   for (i=0; i<n; i++): ids[i] = UNVISITED
 *   for (i=0; i<n; i++):
 *     if (ids[i] == UNVISITED):
 *       dfs(i)
 *   return low
 *
 * function dfs(at):
 *   stack.push(at)
 *   onStack[at] = true
 *   ids[at] = low[at] = id++
 *
 *   # Visited all neighbours of 'at'
 *   # if we're at the start of a SCC empty the seen
 *   # stack until we're back to the start of the SCC.
 *   if (ids[at] == low[at]):
 *     for (node = stack.pop();;node = stack.pop()):
 *       onSatck[node] = false
 *       low[node] = ids[at]
 *       if (node == at): break
 *     sccCount++
 *
 */
#ifndef D_GRAPH_TARJANSCC_H
#define D_GRAPH_TARJANSCC_H

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


class TarjanSccSolverAdjacencyList {
public:
  using SCC_LIST = std::unordered_map<int, std::set<int>>;
private:
  const double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
  const double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();
  const int UNVISITED = -1;

  Graph *graph_;
  unsigned N_;

  bool solved_;
  int sccCount_, id_;
  std::vector<bool> onStack_;
  std::vector<int> ids_, low_;
  std::stack<int> stack_;

  void solve() {
    if (solved_) return;
    for (unsigned i = 0; i < N_; i++) if (ids_[i] == UNVISITED) dfs(i);
    solved_ = true;
  }


  void dfs(int at) {
    stack_.push(at);
    onStack_[at] = true;
    ids_[at] = low_[at] = id_++;

    auto graphItr = (*graph_)()->find(at);
    if (graphItr != (*graph_)()->end()) {
      if (!graphItr->second.empty()) {
        for (auto edge: graphItr->second) {
          if (ids_[edge.first] == UNVISITED) dfs(edge.first);
          if (onStack_[edge.first]) low_[at] = std::min(low_[at], low_[edge.first]);
        }
      }
    }

    // On recursive callback, if we're at the root node (start of SCC)
    // empty the seen stack until back to root.
    if (ids_[at] == low_[at]) {
      while (!stack_.empty()) {
        int node = stack_.top();
        stack_.pop();
        onStack_[node] = false;
        low_[node] = ids_[at];
        if (node == at) break;
      }
      sccCount_++;
    }
  }

public:
  TarjanSccSolverAdjacencyList(const TarjanSccSolverAdjacencyList&) = delete;
  TarjanSccSolverAdjacencyList& operator=(TarjanSccSolverAdjacencyList const&) = delete;

  TarjanSccSolverAdjacencyList(Graph *graph) {
    if (graph == nullptr) throw std::invalid_argument("GRAPH NULL");
    N_ = graph->size();
    if (N_ == 0) throw std::invalid_argument("GRAPH Empty");
    graph_ = graph;

    low_.resize(N_, -1); // Low link values
    ids_.resize(N_, UNVISITED); // Nodes ids
    onStack_.resize(N_, false);
    id_ = 0;
    solved_ = false;
    sccCount_ = 0;
  }


  const Graph& operator()() {
    return *graph_;
  }


  // Returns the number of strongly connected components in the graph.
  int sccCount() {
    if (!solved_) solve();
    return sccCount_;
  }


  // Get the connected components of this graph. If two indexes
  // have the same value then they're in the same SCC.
  std::set<std::set<int>> getSccs() {
    if (!solved_) solve();

    std::unordered_map<int, std::set<int>> sccMAP;
    std::set<std::set<int>> sccList;

    for (unsigned i = 0; i < N_; i++) {
      auto itr = sccMAP.find(low_[i]);
      if (itr == sccMAP.end()) {
    	sccMAP[low_[i]] = std::set<int>{};
        itr = sccMAP.find(low_[i]);
      }
      itr->second.insert(i);
    }

	for (auto scc : sccMAP) {
	  if (!scc.second.empty()) {
        sccList.insert(scc.second);
	  }
	}

    return std::move(sccList);
  }


  static void printSCCList(const std::set<std::set<int>> &sccList) {
	for (auto scc : sccList) {
	  std::cout << "Nodes: [";
	  for (auto edge: scc) {
	    std::cout << edge << ",";
	  }
	  std::cout << "] form a Strongly Connected Component." << std::endl;
	}
    return;
  }

};



// Example usage of TarjanScc
int TarjanScc_test()
{
  Graph graph(8);

  graph.addDirectedEdge(6, 0);
  graph.addDirectedEdge(6, 2);
  graph.addDirectedEdge(3, 4);
  graph.addDirectedEdge(6, 4);
  graph.addDirectedEdge(2, 0);
  graph.addDirectedEdge(0, 1);
  graph.addDirectedEdge(4, 5);
  graph.addDirectedEdge(5, 6);
  graph.addDirectedEdge(3, 7);
  graph.addDirectedEdge(7, 5);
  graph.addDirectedEdge(1, 2);
  graph.addDirectedEdge(7, 3);
  graph.addDirectedEdge(5, 0);

  std::unique_ptr<TarjanSccSolverAdjacencyList> solver = std::make_unique<TarjanSccSolverAdjacencyList>(&graph);
  std::set<std::set<int>> sccList = solver->getSccs();
/*
  for (int i = 0; i < 8; i++) {
    auto itr = multimap.find(sccs[i]);
    if (itr == multimap.end()) {
      multimap.insert(std::make_pair(sccs[i], 0));
      itr = multimap.find(sccs[i]);
    }
    itr->second.push_back(i);
//    std::cout << "add: " << sccs[i] << "," << i << std::endl;
  }
*/
  // Prints:
  // Number of Strongly Connected Components: 3
  // Nodes: [0, 1, 2] form a Strongly Connected Component.
  // Nodes: [3, 7] form a Strongly Connected Component.
  // Nodes: [4, 5, 6] form a Strongly Connected Component.
  std::cout << "Number of Strongly Connected Components: " << solver->sccCount() << std::endl;
  TarjanSccSolverAdjacencyList::printSCCList(sccList);

  solver = nullptr;
  return 0;
}

} // namespace dsa

#endif /* D_GRAPH_TARJANSCC_H */
