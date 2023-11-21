/*
 * @file   ArticulationPointsAdjacencyList.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) mingy, enyala9733@gmail.com
 * @date   21 November 2023
 * @version 0.1
 * @brief   An implementation of Tarjan's algorithm to find ArticulationPoints using an adjacency list.
 * Time complexity: O(V+E)
 *
 */
#ifndef D_GRAPH_ARTICULATIONPOINT_H
#define D_GRAPH_ARTICULATIONPOINT_H

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
  using std::vector;
  using std::min;
  using std::max;
  class ArticulationPointsAdjacencyList {
  private:
    int n, id, rootNodeOutcomingEdgeCount;
    bool solved;
    vector<int>low, ids;
    vector<bool>visited, isArticulationPoint;
    Graph* graph;
  public:
    ArticulationPointsAdjacencyList(Graph* graph_) {
      if (graph_ == nullptr) throw std::invalid_argument("GRAPH NULL");
      n = graph_->size();
      if (n == 0)throw std::invalid_argument("GRAPH NULL");
      graph = graph_;
    }

    // Returns the indexes for all articulation points in the graph even if the
    // graph is not fully connected.
    vector<bool> findArticulationPoints() {
      if (solved) return isArticulationPoint;
      id = 0;
      low.resize(n); // Low link values
      ids.resize(n); // Nodes ids
      visited.resize(n);
      isArticulationPoint.resize(n);
      for (int i = 0; i < n; i++) {
        if (!visited[i]) {
          rootNodeOutcomingEdgeCount = 0;
          dfs(i, i, -1);
          isArticulationPoint[i] = (rootNodeOutcomingEdgeCount > 1);
        }
      }
      solved = true;
      return isArticulationPoint;
    }
    void dfs(int root, int at, int parent) {
      if (parent == root) rootNodeOutcomingEdgeCount++;
      visited[at] = true;
      low[at] = ids[at] = id++;

      vector<int> edges = graph->getNebWithoutWeight(at);
      for (int to : edges) {
        if (to == parent) continue;
        if (!visited[to]) {
          dfs(root, to, at);
          low[at] = min(low[at], low[to]);
          if (ids[at] <= low[to]) {
            isArticulationPoint[at] = true;
          }
        }
        else {
          low[at] = min(low[at], ids[to]);
        }
      }
    }
  };
}

int ArticulationPointsTest() {
  int n = 9;
  Graph graph(n);
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
  std::unique_ptr<ArticulationPointsAdjacencyList> solver =
    std::make_unique<ArticulationPointsAdjacencyList>(&graph);
  auto articulation_point = solver->findArticulationPoints();
  for (int i = 0; i < articulation_point.size(); ++i)
    if (articulation_point[i])cout << i << " ";

  solver = nullptr;
  return 0;
}
#endif
