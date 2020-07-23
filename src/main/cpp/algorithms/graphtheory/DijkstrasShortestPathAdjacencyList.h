/*
 * @file   DijkstrasShortestPathAdjacencyList.h
 * @author @author William Fiset, william.alexandre.fiset@gmail.com
 *                 Converted from JAVA to C++ by:
 *                 Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   10 July 2020
 * @version 0.1
 * @brief   An implementation of the Dijkstras Shortest Path
 * This file contains an implementation of Dijkstra's shortest path algorithm from a start node to a
 * specific ending node. Dijkstra can also be modified to find the shortest path between a starting
 * node and all other nodes in the graph. However, in this implementation since we're only going
 * from a starting node to an ending node we can employ an optimization to stop early once we've
 * visited all the neighbors of the ending node.

# Runs Dijkstra's algorithm and returns an array that contains
# the shortest distance to every node from the start nose s.
# g - adjacency of nodes in the graph
# n - the number of nodes in the graph
# s - the index of the starting node (0 <= s < n)
function dijkstra(g, n, s, e):
  vis = [false, false, ..., false] # size n
  prev = [null, null, ..., null] # size n
  dist = [inf, inf, ..., inf, inf] # size n
  dist[s] = 0
  pq = empty priority queue
  pq.insert(s, 0)
  while pq.size() != 0:
    index, minValue = pq.poll()
    vis[index] = true
    for (edge : g[index]):
      if vis[edge.to]: continue
      newDist = dist[index] + edge.cost
      if newDist < dist[edge.to]:
        prev[edge.to] = index
        dist[edge.to] = newDist
        pq.insert(edge.to, newDist)
    if index == e:
      return dist[e]
  return inf


# Finds the shortest path between two nodes.
# g - adjacency list of weighted graph
# n - the number of nodes in the graph
# s - the index of the starting node (0 <= s < n)
# e - the index of the end node (0 <= s < n)
function findShortestPath(g, n, s, e):
  dist , prev = dijkstra(g, n ,s)
  path = []
  if (dist[e] == inf) return path
  for (at = e; at != null; at = prev[at])
    path.add(at)
  path.reverse()
  return path
 */

#ifndef D_GRAPH_DIJKSTRASHORTESTPATH_H
#define D_GRAPH_DIJKSTRASHORTESTPATH_H

#include <Graph.h>

#include <vector>
#include <deque>
#include <queue>          // std::priority_queue
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
#include <cmath>        // std::abs

namespace dsa {


// Node class to track the nodes to visit while running Dijkstra's
class Node {
  static constexpr double eps = std::numeric_limits<double>::epsilon();

public:
  int id_;
  double value_;

  Node(int id, double value):id_(id), value_(value) {
  }

  Node(const Node& rhs) { // Copy constructor
    id_ = rhs.id_;
    value_ = rhs.value_;
  }

  Node(const Node&& rhs) { // Move constructor
    id_ = rhs.id_;
    value_ = rhs.value_;
  }

  Node& operator=(const Node& other) // copy assignment
  {
    if (this != &other) { // self-assignment check expected
      id_ = other.id_;
      value_ = other.value_;
    }
    return *this;
  }

  Node& operator=(Node&& other) noexcept // move assignment
  {
    if(this != &other) { // no-op on self-move-assignment (delete[]/size=0 also ok)
      id_ = other.id_;
      value_ = other.value_;
    }
    return *this;
  }

  // overload function call
  Node operator()(int id, double value) {
	Node N(id, value);
    return N;
  }

  friend int operator<(const Node& l, const Node& r)
  {
    if (std::abs(l.value_ - r.value_) < eps) return 0;
    return (l.value_ - r.value_) > 0 ? +1 : -1;
  }

//  inline int operator> (const Node& lhs, const Node& rhs){ return rhs < lhs; }
//  inline bool operator<=(const X& lhs, const X& rhs){ return !(lhs > rhs); }
//  inline bool operator>=(const X& lhs, const X& rhs){ return !(lhs < rhs); }


  std::string toString() const {
	std::stringstream os;
    os << "Node(" << "ID:" << id_ << ",value:" << value_ << ")";
    return os.str();
  }

  friend std::ostream& operator<<(std::ostream &strm, const Node &n) {
    return strm << n.toString();
  }

};


class nodeComparison
{
  bool reverse_;
public:
  nodeComparison(const bool& revparam=false) {
    reverse_ = revparam;
  }

  bool operator() (const Node& l, const Node&r) const {
    if (reverse_) return (l.value_ > r.value_);
    else return (l.value_ < r.value_);
  }
};

typedef std::priority_queue<Node, std::vector<Node>, nodeComparison> nodepq_type;
using NODE_PQ = std::priority_queue<Node, std::vector<Node>, nodeComparison>;


class DijkstrasShortestPathAdjacencyList {
private:
  const double inf = std::numeric_limits<double>::infinity();
  const double negInf = -std::numeric_limits<double>::infinity();

  int N_;
  std::vector<double> dist_;
  std::vector<int> prev_;
  Graph *graph_;

  // Run Dijkstra's algorithm on a directed graph to find the shortest path
  // from a starting node to an ending node. If there is no path between the
  // starting node and the destination node the returned value is set to be
  // Double.POSITIVE_INFINITY.
  double dijkstra(int start, int end) {
    // Maintain an array of the minimum distance to each node
    dist_.resize(N_, inf);
    dist_[start] = 0;

    // Keep a priority queue of the next most promising node to visit.
    NODE_PQ pq;
    pq.push(Node(start, 0));

    // Array used to track which nodes have already been visited.
    std::vector<bool> visited;
    visited.resize(N_, false);
    prev_.resize(N_, -1);

    while (!pq.empty()) {
      Node node = pq.top();
      pq.pop();
      visited[node.id_] = true;

      // We already found a better path before we got to
      // processing this node so we can ignore it.
      if (dist_[node.id_] < node.value_) continue;

      auto graphItr = (*graph_)()->find(node.id_);
      if (graphItr != (*graph_)()->end()) {
        if (!graphItr->second.empty()) {
          for (auto edge: graphItr->second) {
            // You cannot get a shorter path by revisiting
            // a node you have already visited before.
            if (visited[edge.first]) continue;

            // Relax edge by updating minimum cost if applicable.
            double newDist = dist_[graphItr->first] + edge.second;
            if (newDist < dist_[edge.first]) {
              prev_[edge.first] = graphItr->first;
              dist_[edge.first] = newDist;
              pq.push(Node(edge.first, dist_[edge.first]));
            }
          }
        }
      }

      // Once we've visited all the nodes spanning from the end
      // node we know we can return the minimum distance value to
      // the end node because it cannot get any better after this point.
      if (node.id_ == end) return dist_[end];
    }
    // End node is unreachable
    return inf;
  }


  // Initialize the solver by providing the graph size and a starting node. Use the {@link #addEdge}
  // method to actually add edges to the graph.
  //
  // @param n - The number of nodes in the graph.
  //
public:
  DijkstrasShortestPathAdjacencyList(Graph *graph) {
    if (graph == nullptr) throw std::invalid_argument("GRAPH NULL");
    N_ = graph->size();
    graph_ = graph;
  }

  DijkstrasShortestPathAdjacencyList(const DijkstrasShortestPathAdjacencyList&) = delete;
  DijkstrasShortestPathAdjacencyList& operator=(DijkstrasShortestPathAdjacencyList const&) = delete;

  // Use {@link #addEdge} method to add edges to the graph and use this method
  // to retrieve the constructed graph.
  const Graph& operator()() {
    return *graph_;
  }



  // Reconstructs the shortest path (of nodes) from 'start' to 'end' inclusive.
  //
  // @return An array of nodes indexes of the shortest path from 'start' to 'end'. If 'start' and
  //     'end' are not connected then an empty array is returned.
  //
  std::list<int> reconstructPath(int start, int end) {
    if (end < 0 || end >= N_) throw std::invalid_argument("Invalid node index");
    if (start < 0 || start >= N_) throw std::invalid_argument("Invalid node index");
    double dist = dijkstra(start, end);
    std::list<int> path;
    if (dist == inf) return path;
    for (int at = end; at != -1; at = prev_[at])
      path.push_front(at);
//    for (int at : prev_) if (at != -1) path.push_back(at);
    return path;
  }

};



// Example usage of DijkstrasShortestPath
int DijkstrasShortestPath_test()
{
  Graph graph(8);

  graph.addDirectedEdge(6, 0, 1.1);
  graph.addDirectedEdge(6, 2, 0.2);
  graph.addDirectedEdge(3, 4, 3.6);
  graph.addDirectedEdge(6, 4, 0.4);
  graph.addDirectedEdge(2, 0, 0.7);
  graph.addDirectedEdge(0, 1, 3.4);
  graph.addDirectedEdge(4, 5, 6.9);
  graph.addDirectedEdge(5, 6, 0.9);
  graph.addDirectedEdge(3, 7, 8.2);
  graph.addDirectedEdge(7, 5, 0.3);
  graph.addDirectedEdge(1, 2, 4.6);
  graph.addDirectedEdge(7, 3, 6.4);
  graph.addDirectedEdge(5, 0, 10.1);

  try {
    std::unique_ptr<DijkstrasShortestPathAdjacencyList> solver = std::make_unique<DijkstrasShortestPathAdjacencyList>(&graph);

    int start = 3, end = 0;

    std::list<int> path = solver->reconstructPath(start, end);

    std::cout << "Dijkstras Shortest Path from " << start << " to " << end << ": [";
    if (!path.empty()) {
      for (auto edge: path){
        std::cout << edge << ",";
      }
    }
    std::cout << "]" << std::endl;

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

#endif /* D_GRAPH_DIJKSTRASHORTESTPATH_H */
