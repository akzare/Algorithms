/*
 * @file   RootingTree.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   16 July 2020
 * @version 0.1
 * @brief   Often when working with trees we are given them as a graph with undirected edges, however
 * sometimes a better representation is a rooted tree.
 *
 * <p>Time Complexity: O(V+E)
 *
 */

#ifndef D_ROOTINGTREE_H
#define D_ROOTINGTREE_H

#include <Graph.h>

#include <vector>
#include <deque>
#include <queue>
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

#include <chrono>
#include <random>
#include <sstream>
#include <memory>
#include <iostream>
#include <cmath>

namespace dsa {


class RootingTree {
public:
  class TreeNode {
  private:
    int id_;
    TreeNode *parent_;
    std::unordered_set<TreeNode*> children_;
  public:
    // Useful constructor for root node.
    TreeNode(int id) : TreeNode(id, nullptr) {
    }

    TreeNode(int id, TreeNode *parent) {
      id_ = id;
      parent_ = parent;
    }

    virtual ~TreeNode() {
      for (auto c : children_) {
        if (c) delete c;
      }
    }

    TreeNode(const TreeNode& rhs) { // Copy constructor
  	  std::cout << "TreeNode copy constructor" << std::endl;
  	  id_ = rhs.id_;
  	  parent_ = rhs.parent_;
      children_ = rhs.children_;
    }

    TreeNode(const TreeNode&& rhs) { // Move constructor
      id_ = rhs.id_;
      parent_ = rhs.parent_;
      children_ = rhs.children_;
    }

    TreeNode& operator = (const TreeNode& rhs) {
      if (this != &rhs) {
        id_ = rhs.id_;
        parent_ = rhs.parent_;
        children_ = rhs.children_;
  	  }
  	  return *this;
    }

    // overloaded == operator
    bool operator ==(const TreeNode& rhs) {
       if(id_ == rhs.id_) {
          return true;
       }
       return false;
    }

    void addChildren(TreeNode *node) {
      children_.insert(node);
    }

    int id() {
      return id_;
    }

    TreeNode* parent() {
      return parent_;
    }

    const std::unordered_set<TreeNode*>& children() {
      return children_;
    }

    std::string toString() const {
  	  std::stringstream os;
      os << id_;
      return os.str();
    }

    friend std::ostream& operator<<(std::ostream &strm, const TreeNode &tn) {
      return strm << tn.toString();
    }

  };

private:
  TreeNode *root_;
  Graph *graph_;

public:
  RootingTree(Graph *graph, int rootId) {
    if (graph == nullptr) throw std::invalid_argument("GRAPH NULL");
	graph_ = graph;
    root_ = new TreeNode(rootId);
    root_ = buildTree(root_);
  }

  virtual ~RootingTree() {
    if (root_) delete root_;
    root_ = nullptr;
  }

  TreeNode& operator()() {
    return *root_;
  }

  const std::unordered_set<TreeNode*>& children() {
    return root_->children();
  }

  std::string toString() const {
	std::stringstream os;
    os << *root_;
    return os.str();
  }

  friend std::ostream& operator<<(std::ostream &strm, const RootingTree &rt) {
    return strm << rt.toString();
  }

private:
  // Do dfs to construct rooted tree.
  TreeNode *buildTree(TreeNode *node) {

    auto graphItr = (*graph_)()->find(node->id());
    if (graphItr == (*graph_)()->end()) return node;

    if (!graphItr->second.empty()) {
      for (auto edge: graphItr->second) {

        // Ignore adding an edge pointing back to parent.
        if (node->parent() != nullptr) {
          if (edge.first == node->parent()->id()) {
            continue;
          }
        }

        TreeNode *child = new TreeNode(edge.first, node);
        node->addChildren(child);

        buildTree(child);
      }
    }

    return node;
  }

};


void RootingTree_test()
{
  Graph graph(9);

  graph.addUndirectedEdge(0, 1);
  graph.addUndirectedEdge(2, 1);
  graph.addUndirectedEdge(2, 3);
  graph.addUndirectedEdge(3, 4);
  graph.addUndirectedEdge(5, 3);
  graph.addUndirectedEdge(2, 6);
  graph.addUndirectedEdge(6, 7);
  graph.addUndirectedEdge(6, 8);

  // Rooted at 6 the tree should look like:
  //           6
  //      2    7     8
  //    1   3
  //  0    4 5

  RootingTree *root = new RootingTree(&graph, 6);

  // Layer 0: [6]
  std::cout << "Layer 0: [6]: ";
  std::cout << (*root) << std::endl;


#define PRINT_CHILDREN(r) \
  do { \
	std::cout << "["; \
	for (auto c : r) std::cout << (*c) << ","; \
	std::cout << "]"; \
  } while(0)


  // Layer 1: [2, 7, 8]
  std::unordered_set<RootingTree::TreeNode*> children_root = root->children();
  std::cout << "Layer 1: [2, 7, 8]: ";
  PRINT_CHILDREN(children_root);
  std::cout << std::endl;


  // Layer 2: [1, 3]
  int expectedId = 2;
  auto idComparer = [&expectedId](auto c2) -> bool { return ((*c2).id() == expectedId); };
  auto itr = std::find_if(children_root.begin(), children_root.end(), idComparer);
  std::unordered_set<RootingTree::TreeNode*> children_layer2 = (*itr)->children();
  std::cout << "Layer 2: [1, 3]: ";
  PRINT_CHILDREN(children_layer2);
  std::cout << std::endl;


  // Layer 3: [0], [4, 5]
  expectedId = 3;
  itr = std::find_if(children_layer2.begin(), children_layer2.end(), idComparer);
  std::unordered_set<RootingTree::TreeNode*> children_layer3 = (*itr)->children();
  std::cout << "Layer 3: [4, 5]: ";
  PRINT_CHILDREN(children_layer3);
  std::cout << std::endl;
}

} // namespace dsa

#endif /* D_ROOTINGTREE_H */
