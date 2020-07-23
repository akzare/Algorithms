/*
 * @file   Graph.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   07 July 2020
 * @version 0.1
 * @brief   An implementation of Graph with an adjacency list.
 */

#ifndef D_GRAPH_H
#define D_GRAPH_H

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

class Graph
{

public:

  using GRAPH_EDGE = std::unordered_map<int, double>; // Node ID, Cost
  using GRAPH_VERTEX = std::unordered_map<int, GRAPH_EDGE>; // Node ID, Edges

private:
  GRAPH_VERTEX *vertices_;
  int edgeCount_;

public:
  Graph(int n) {
    vertices_ = new GRAPH_VERTEX();
    for (int i = 0; i < n; i++) {
      GRAPH_EDGE edge_;
      vertices_->insert(make_pair(i, std::move(edge_)));
    }
    edgeCount_ = 0;
  }


  virtual ~Graph() {
	if (vertices_) {
      delete vertices_;
      vertices_ = nullptr;
	}
  }


  Graph(const Graph& rhs) { // Copy constructor
	std::cout << "Graph copy constructor" << std::endl;
	vertices_ = rhs.vertices_;
	edgeCount_ = rhs.edgeCount_;
  }


  Graph(const Graph&& rhs) { // Move constructor
	std::cout << "Graph move constructor" << std::endl;
    vertices_ = rhs.vertices_;
	edgeCount_ = rhs.edgeCount_;
  }


  Graph& operator = (const Graph& rhs ) {
	std::cout << "Graph copy operator" << std::endl;
	if (this != &rhs) {
      for (auto it = rhs.vertices_->begin();; it++) {
    	if (it == rhs.vertices_->end()) break;
    	GRAPH_EDGE edges;
	    if (!it->second.empty()) {
	      for (auto edge: it->second) {
	    	edges.insert(std::move(edge));
	      }
	    }
        vertices_->insert(make_pair(it->first, std::move(edges)));
      }
	}
	std::cout << "Graph copy operator DONE" << std::endl;

	return *this;
  }

  Graph& operator = (Graph&& rhs ) {
    std::cout << "Graph move operator" << std::endl;
	if (this != &rhs) {
      vertices_ = rhs.vertices_;
	}
	return *this;
  }

  GRAPH_VERTEX* operator()() {
    return vertices_;
  }


  // Empty this graph
  void clear() {
    for (auto itr = vertices_->begin(); itr != vertices_->end(); itr++)
      itr->second.erase(itr->second.begin(), itr->second.end());
    vertices_->erase(vertices_->begin(), vertices_->end());
  }


  // Get size of graph
  unsigned int size() {
    return vertices_->size();
  }


  // Get number of edges
  unsigned int edgeCount() {
    return edgeCount_;
  }


  // Add a directed edge from node 'u' to node 'v' with cost 'cost'.
  //
  //  Adds a directed edge to the graph.
  //
  //  @param from - The index of the node the directed edge starts at.
  //  @param to - The index of the node the directed edge end at.
  //  @param cost - The cost of the edge.
  //
  void addDirectedEdge(int u, int v, double cost = 0.0) {
	(*vertices_)[u][v] = cost;
    edgeCount_++;
  }


  // Add an undirected edge between nodes 'u' and 'v'.
  void addUndirectedEdge(int u, int v, double cost = 0.0) {
    addDirectedEdge(u, v, cost);
    addDirectedEdge(v, u, cost);
  }


  // Add an undirected un-weighted edge between nodes 'u' and 'v'. The edge added
  // will have a weight of 1 since its intended to be unweighted.
  void addUnweightedUndirectedEdge(int u, int v) {
    addUndirectedEdge(u, v, 0.0);
  }


  static std::string formatPath(int start, int end, std::list<int>& path) {
    std::stringstream ss;
    ss << "Path(" << start << ":" << end << ")[";
    if (path.size()) {
      for (auto node: path) {
        ss << " -> ";
        ss << node;
      }
    }
    ss << "]";
    std::string s = ss.str();

    return s;
  }


  std::string toString() const {
	std::stringstream os;
    os << "Graph[" << std::endl;

    for (auto it = vertices_->begin();; it++) {
  	  if (it == vertices_->end()) break;
      os << " Node(" << it->first << ")[";
	  if (!it->second.empty()) {
	    for (auto edge: it->second) {
          os << "Edge(" << "->" << edge.first << ",cost:" << edge.second << ")";
		  os << ",";
	    }
	  }
      os << "]" << std::endl;
    }

    os << "]";

    return os.str();
  }


  friend std::ostream& operator<<(std::ostream &strm, const Graph &g) {
    return strm << g.toString();
  }

};

} // namespace dsa

#endif /* D_GRAPH_H */
