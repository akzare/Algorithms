/*
 * @file   DijkstrasShortestPathAdjacencyListWithDHeap.h
 * @author @author William Fiset, william.alexandre.fiset@gmail.com
 *                 Converted from JAVA to C++ by:
 *                 Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   10 July 2020
 * @version 0.1
 * @brief   An implementation of the Dijkstras Shortest Path
 * This file contains an implementation of Dijkstra's shortest path algorithm from a start node to a
 * specific ending node. Dijkstra's can also be modified to find the shortest path between a
 * starting node and all other nodes in the graph with minimal effort.

Lazy implementation inserts duplicate key-value pairs in PQ,
because it's more efficient to insert a new key-value pair
in O(log(n)) than it is to update an existing key's
value in O(n). It is inefficient for dense graphs.
The eager version avoids duplicate key-value pairs by
using an Indexed Priority Queue (IPQ).
 */
#ifndef D_GRAPH_DIJKSTRASHORTESTPATHDHEAP_H
#define D_GRAPH_DIJKSTRASHORTESTPATHDHEAP_H

#include <Graph.h>

#include <vector>
#include <deque>
#include <queue> // std::priority_queue
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
#include <cmath>      // std::abs

namespace dsa {


template<typename T>
class MinIndexedDHeap {

  // Current number of elements in the heap.
  int sz_;

  // Maximum number of elements in the heap.
  int N_;

  // The degree of every node in the heap.
  int D_;

  // Lookup arrays to track the child/parent indexes of each node.
  std::vector<int> child_, parent_;

  // The Position Map (pm) maps Key Indexes (ki) to where the position of that
  // key is represented in the priority queue in the domain [0, sz).
  std::vector<int> pm_;

  // The Inverse Map (im) stores the indexes of the keys in the range
  // [0, sz) which make up the priority queue. It should be noted that
  // 'im' and 'pm' are inverses of each other, so: pm[im[i]] = im[pm[i]] = i
  std::vector<int> im_;

  // The values associated with the keys. It is very important  to note
  // that this array is indexed by the key indexes (aka 'ki').
  std::vector<T> values_;

public:
  MinIndexedDHeap(const MinIndexedDHeap&) = delete;
  MinIndexedDHeap& operator=(MinIndexedDHeap const&) = delete;

  // Initializes a D-ary heap with a maximum capacity of maxSize.
  MinIndexedDHeap(int degree, int maxSize) {
    if (maxSize <= 0) throw std::invalid_argument("maxSize <= 0");

    sz_ = 0;
    D_ = std::max(2, degree);
    N_ = std::max(D_ + 1, maxSize);

    im_.resize(N_, 0);
    pm_.resize(N_, 0);
    child_.resize(N_, 0);
    parent_.resize(N_, 0);
    values_.resize(N_);

    for (int i = 0; i < N_; i++) {
      parent_[i] = (i - 1) / D_;
      child_[i] = i * D_ + 1;
      pm_[i] = im_[i] = -1;
    }
  }

  ~MinIndexedDHeap() {
  }

  int size() {
    return sz_;
  }

  bool isEmpty() {
    return sz_ == 0;
  }

  bool contains(int ki) {
    keyInBoundsOrThrow(ki);
    return pm_[ki] != -1;
  }

  int peekMinKeyIndex() {
    isNotEmptyOrThrow();
    return im_[0];
  }

  int pollMinKeyIndex() {
    int minki = peekMinKeyIndex();
    deleteObj(minki);
    return minki;
  }

  T peekMinValue() {
    isNotEmptyOrThrow();
    return values_[im_[0]];
  }

  T pollMinValue() {
    T minValue = peekMinValue();
    deleteObj(peekMinKeyIndex());
    return minValue;
  }

  void insert(int ki, T value) {
    if (contains(ki)) throw std::invalid_argument("index already exists; received: " + ki);
    valueNotNullOrThrow(value);
    pm_[ki] = sz_;
    im_[sz_] = ki;
    values_[ki] = value;
    swim(sz_++);
  }

  T valueOf(int ki) {
    keyExistsOrThrow(ki);
    return values_[ki];
  }

  void deleteObj(int ki) {
    keyExistsOrThrow(ki);
    int i = pm_[ki];
    swap(i, --sz_);
    sink(i);
    swim(i);
//    values_.erase(values_.begin()+ki);
    values_[ki] = 0;
    pm_[ki] = -1;
    im_[sz_] = -1;
  }

  T update(int ki, T value) {
    keyExistsAndValueNotNullOrThrow(ki, value);
    int i = pm_[ki];
    T oldValue = values_[ki];
    values_[ki] = value;
    sink(i);
    swim(i);
    return oldValue;
  }

  // Strictly decreases the value associated with 'ki' to 'value'
  void decrease(int ki, T value) {
    keyExistsAndValueNotNullOrThrow(ki, value);
    if (value < values_[ki]) {
      values_[ki] = value;
      swim(pm_[ki]);
    }
  }

  // Strictly increases the value associated with 'ki' to 'value'
  void increase(int ki, T value) {
    keyExistsAndValueNotNullOrThrow(ki, value);
    if (values_[ki] < value) {
      values_[ki] = value;
      sink(pm_[ki]);
    }
  }

  // Helper functions

  void sink(int i) {
    for (int j = minChild(i); j != -1; ) {
      swap(i, j);
      i = j;
      j = minChild(i);
    }
  }

  void swim(int i) {
    while (i < parent_[i]) {
      swap(i, parent_[i]);
      i = parent_[i];
    }
  }

  // From the parent node at index i find the minimum child below it
  int minChild(int i) {
    int index = -1, from = child_[i], to = std::min(sz_, from + D_);
    for (int j = from; j < to; j++) if (j < i) index = i = j;
    return index;
  }

  void swap(int i, int j) {
    pm_[im_[j]] = i;
    pm_[im_[i]] = j;
    int tmp = im_[i];
    im_[i] = im_[j];
    im_[j] = tmp;
  }

  // Tests if the value of node i < node j
  bool less(int i, int j) {
    return (values_[im_[i]] < values_[im_[j]]);
  }

  std::string toString() {
    std::stringstream str;
    for (int i = 0; i < sz_; i++) {
      str << im_[i];
      str << " ";
    }
    return str.str();
  }

  // Helper functions to make the code more readable.
  void isNotEmptyOrThrow() {
    if (isEmpty()) throw std::invalid_argument("Priority queue underflow");
  }

  void keyExistsAndValueNotNullOrThrow(int ki, T value) {
    keyExistsOrThrow(ki);
    valueNotNullOrThrow(value);
  }

  void keyExistsOrThrow(int ki) {
    if (!contains(ki)) throw std::out_of_range("Index does not exist; received: " + ki);
  }

  void valueNotNullOrThrow(T value) {
  // if (value == nullptr) throw std::invalid_argument("value cannot be null");
  }

  void keyInBoundsOrThrow(int ki) {
    if (ki < 0 || ki >= N_)
      throw std::invalid_argument("Key index out of bounds; received: " + ki);
  }
};



class DijkstrasShortestPathAdjacencyListWithDHeap {
private:
  const double inf = std::numeric_limits<double>::infinity();

  int N_;
  int edgeCount_;
  std::vector<double> dist_;
  std::vector<int> prev_;
  Graph *graph_;

  // Run Dijkstra's algorithm on a directed graph to find the shortest path
  // from a starting node to an ending node. If there is no path between the
  // starting node and the destination node the returned value is set to be
  // Double.POSITIVE_INFINITY.
  double dijkstra(int start, int end) {

    // Keep an Indexed Priority Queue (ipq) of the next most promising node
    // to visit.
    int degree = edgeCount_ / N_;
 //    std::unique_ptr<MinIndexedDHeap> ipq{ new MinIndexedDHeap<double>(degree, N_) };
    std::unique_ptr<MinIndexedDHeap<double>> ipq = std::make_unique<MinIndexedDHeap<double>>(degree, N_);

//    MinIndexedDHeap<double> ipq (degree, N_);

    ipq->insert(start, 0.0);

    // Maintain an array of the minimum distance to each node.
    dist_.resize(N_, inf);
    dist_[start] = 0;

    std::vector<bool> visited;
    visited.resize(N_, false);
    prev_.resize(N_, -1);

    while (!ipq->isEmpty()) {
      int nodeId = ipq->peekMinKeyIndex();

      visited[nodeId] = true;
      double minValue = ipq->pollMinValue();

      // We already found a better path before we got to
      // processing this node so we can ignore it.
      if (minValue > dist_[nodeId]) continue;

      auto graphItr = (*graph_)()->find(nodeId);
      if (graphItr != (*graph_)()->end()) {
        if (!graphItr->second.empty()) {
          for (auto edge: graphItr->second) {

            // We cannot get a shorter path by revisiting
            // a node we have already visited before.
            if (visited[edge.first]) continue;

            // Relax edge by updating minimum cost if applicable.
            double newDist = dist_[nodeId] + edge.second;
            if (newDist < dist_[edge.first]) {
              prev_[edge.first] = nodeId;
              dist_[edge.first] = newDist;
              // Insert the cost of going to a node for the first time in the PQ,
              // or try and update it to a better value by calling decrease.
              if (!ipq->contains(edge.first)) ipq->insert(edge.first, newDist);
              else ipq->decrease(edge.first, newDist);
            }
          }
        }
      }

      // Once we've processed the end node we can return early (without
      // necessarily visiting the whole graph) because we know we cannot get a
      // shorter path by routing through any other nodes since Dijkstra's is
      // greedy and there are no negative edge weights.
      if (nodeId == end) return dist_[end];
    }
    // End node is unreachable.
    return inf;
  }


  // Initialize the solver by providing the graph size and a starting node. Use the {@link #addEdge}
  // method to actually add edges to the graph.
  //
  // @param n - The number of nodes in the graph.
  //
public:
  DijkstrasShortestPathAdjacencyListWithDHeap(Graph *graph) {
    if (graph == nullptr) throw std::invalid_argument("GRAPH NULL");
    N_ = graph->size();
    edgeCount_ = graph->edgeCount();
    graph_ = graph;
  }


  DijkstrasShortestPathAdjacencyListWithDHeap(const DijkstrasShortestPathAdjacencyListWithDHeap&) = delete;
  DijkstrasShortestPathAdjacencyListWithDHeap& operator=(DijkstrasShortestPathAdjacencyListWithDHeap const&) = delete;

  // Use {@link #addEdge} method to add edges to the graph and use this method to retrieve the
  // constructed graph.
  //
  const Graph& operator()() {
    return *graph_;
  }


  // Reconstructs the shortest path (of nodes) from 'start' to 'end' inclusive.
  //
  // @return An array of node indexes of the shortest path from 'start' to 'end'. If 'start' and
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
  //  for (int at : prev_) if (at != -1) path.push_back(at);
    return path;
  }

};



// Example usage of DijkstrasShortestPathDHeap
int DijkstrasShortestPathDHeap_test()
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

  try  {
    std::unique_ptr<DijkstrasShortestPathAdjacencyListWithDHeap> solver = std::make_unique<DijkstrasShortestPathAdjacencyListWithDHeap>(&graph);

    int start = 3, end = 0;

    std::list<int> path = solver->reconstructPath(start, end);

    std::cout << "Dijkstras Shortest Path from " << start << " to " << end << ": [";
    if (!path.empty()){
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

#endif /* D_GRAPH_DIJKSTRASHORTESTPATHDHEAP_H */
