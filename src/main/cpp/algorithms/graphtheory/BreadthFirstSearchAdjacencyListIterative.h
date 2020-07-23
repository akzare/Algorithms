/*
 * @file   BreadthFirstSearchAdjacencyListIterative.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   07 July 2020
 * @version 0.1
 * @brief   An implementation of BFS with an adjacency list.
 *          Time Complexity: O(V + E)


# Global/class scope variables
n = number of nodes in the graph
g = adjacency list representing unweighted graph

# s = start node, e = end node, and 0 <= e, s < n
function bfs(s, e):

  # Do a BFS starting at node s
  prev = solve(s)

  # Return reconstructed path from s -> e
  return reconstructPath(s, e, prev)

function solve(s):
  q = queue data structure with enqueue and dequeue
  q.enqueue(s)

  visisted = [false, ..., false] # size n
  visisted[s] = true

  prev = [null, ..., null] # size n
  while !q.isEmpty():
    node = q.dequeue()
    neighbours = g.get(node)

    for (next :  neighbours):
      if !visisted[next]:
        q.enqueue(next)
        visited[next] = true
        prev[next] = node
  return prev


function reconstructPath(s, e, prev):
  # Reconstruct path going backward from e
  path = []
  for (at=e; at!=null; at=next[at]):
    path.add(at)

  path.reverse()

  # If s and e are connected return the path
  if path[0] == s: return path
  return []

 */

#ifndef D_GRAPH_BREATHFIRSTSEARCH_H
#define D_GRAPH_BREATHFIRSTSEARCH_H

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

namespace dsa {

typedef std::vector<int> IntegerVector;


class BreadthFirstSearchAdjacencyListIterative
{

private:
  Graph *graph_;

  unsigned n_;
  std::vector<int> prev_;

public:
  BreadthFirstSearchAdjacencyListIterative(Graph *graph) {
    if (graph == nullptr) throw std::invalid_argument("GRAPH NULL");
	n_ = graph->size();
    graph_ = graph;
  }

  BreadthFirstSearchAdjacencyListIterative(const BreadthFirstSearchAdjacencyListIterative&) = delete;
  BreadthFirstSearchAdjacencyListIterative& operator=(BreadthFirstSearchAdjacencyListIterative const&) = delete;

  const Graph& operator()() {
    return *graph_;
  }

public:
  // Perform a breadth first search on a graph a starting node 'start'.
  std::vector<int> bfs(int start) {
    std::vector<int> prev(n_, 0);
    std::vector<bool> visited(n_, false);
    std::list<int> queue_;

    if (n_ == 0) return prev;

    if (start < 0 || (unsigned)start >= n_) throw std::invalid_argument("Invalid start node index");

    {
      auto graphItr = (*graph_)()->find(start);
      if (graphItr == (*graph_)()->end()) return prev;
    }

    // Start by visiting the 'start' node and add it to the queue.
    queue_.push_back(start);
    visited[start] = true;

    // Continue until the BFS is done.
    while (!queue_.empty()) {
      int node = queue_.front();
      queue_.pop_front();

//      std::cout << "BFS visiting node: " <<  node << std::endl;
      auto graphItr = (*graph_)()->find(node);
      if (graphItr != (*graph_)()->end()) {
//        std::cout << "Node " << node << " is in graph map" <<  std::endl;
        if (!graphItr->second.empty()) {
//          std::cout << "Node " << node << ", List is not empty" <<  std::endl;
          // Loop through all edges attached to this node. Mark nodes as visited once they're
          // in the queue. This will prevent having duplicate nodes in the queue and speedup the BFS.
          for (auto edge: graphItr->second) {
//        	  std::cout << edge << std::endl;
            if (!visited[edge.first]) {
              visited[edge.first] = true;
              prev[edge.first] = node;
              queue_.push_back(edge.first);

//              std::cout << "    visiting edge: " <<  edge.from_ << " --- (" << edge.cost_ << ") --->" << edge.to_ << std::endl;
            }
            else {
  //           std::cout << "    already visited edge: " <<  edge.from_ << " --- (" << edge.cost_ << ") --->" << edge.to_ << std::endl;
            }
          }
        }

      }
      else {
    	throw std::runtime_error("Key is not in graph map");
      }
    }

    return prev;
  }



  // Reconstructs the path (of nodes) from 'start' to 'end' inclusive. If the edges are unweighted
  // then this method returns the shortest path from 'start' to 'end'
  //
  // @return An array of nodes indexes of the shortest path from 'start' to 'end'. If 'start' and
  //     'end' are not connected then an empty array is returned.
  void reconstructPath(int start, int end, std::list<int> &path) {
	path.clear();
	if (n_ == 0) return;

    if (end < 0 || (unsigned)end >= n_) throw std::invalid_argument("Invalid end node index");
    if (start < 0 || (unsigned)start >= n_) throw std::invalid_argument("Invalid start node index");

    {
      auto graphItr = (*graph_)()->find(start);
      if (graphItr == (*graph_)()->end()) return;
    }

    std::vector<int> prev = bfs(start);
//    std::cout << "prev:" << std::endl;
//    for (int p : prev) std::cout << p << std::endl;
//    std::cout << "start:" << start << " end:" << end << std::endl;

    int idx = end;
    int cntr = prev.size();
    while (idx != start && cntr--) {
//    	std::cout << idx << std::endl;
      path.push_front(idx);
      idx = prev.at(idx);
    }
    if (cntr == -1) path.clear();
    else path.push_front(idx);

    return;
  }

};



// BFS example. 
int bfs_test()
{
  Graph graph(13);
  graph.addUnweightedUndirectedEdge(0, 7);
  graph.addUnweightedUndirectedEdge(0, 9);
  graph.addUnweightedUndirectedEdge(0, 11);
  graph.addUnweightedUndirectedEdge(7, 11);
  graph.addUnweightedUndirectedEdge(7, 6);
  graph.addUnweightedUndirectedEdge(7, 3);
  graph.addUnweightedUndirectedEdge(6, 5);
  graph.addUnweightedUndirectedEdge(3, 4);
  graph.addUnweightedUndirectedEdge(2, 3);
  graph.addUnweightedUndirectedEdge(2, 12);
  graph.addUnweightedUndirectedEdge(12, 8);
  graph.addUnweightedUndirectedEdge(8, 1);
  graph.addUnweightedUndirectedEdge(1, 10);
  graph.addUnweightedUndirectedEdge(10, 9);
  graph.addUnweightedUndirectedEdge(9, 8);


  BreadthFirstSearchAdjacencyListIterative solver(&graph);

  int start = 10, end = 5;
  std::list<int> path;
  solver.reconstructPath(10, 5, path);
  std::cout << "The shortest path: " << Graph::formatPath(start, end, path) << std::endl;
  // Prints:
  // The shortest path from 10 to 5 is: [10 -> 9 -> 0 -> 7 -> 6 -> 5]
  return 0;
}

} // namespace dsa

#endif /* D_GRAPH_BREATHFIRSTSEARCH_H */
