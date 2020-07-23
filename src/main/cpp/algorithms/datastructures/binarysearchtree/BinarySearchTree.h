/*
 * @file   BinarySearchTree.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (C++ multiple iterators) https://blog.cppse.nl/cpp-multiple-iterators-with-traits
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   20 July 2020
 * @version 0.1
 * @brief   This file contains an implementation of a Binary Search Tree (BST) Any comparable data is allowed
 * within this tree (numbers, strings, comparable Objects, etc...). Supported operations include
 * adding, removing, height, and containment checks. Furthermore, multiple tree traversal Iterators
 * are provided including: 1) Preorder traversal 2) Inorder traversal 3) Postorder traversal 4)
 * Levelorder traversal
 */

#ifndef D_BINARYSEARCHTREE_H
#define D_BINARYSEARCHTREE_H

#include <vector>
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

#include <sstream>
#include <memory>
#include <iostream>
#include <type_traits>

namespace dsa {

template <class T> class BinarySearchTree;

template<class T, typename TRAITS> class BinarySearchTreeIterTraits;

template<class T> class BinarySearchTreeIterTraits<T, void>
{
public:
  static typename BinarySearchTree<T>::Node* next(std::stack<typename BinarySearchTree<T>::Node*> &stack,
                                                  std::queue<typename BinarySearchTree<T>::Node*> &queue,
                                                  typename BinarySearchTree<T>::Node* trav) {
    std::cout << "BinarySearchTreeIterTraits<void>::next should not be used" << std::endl;
    throw std::logic_error("BinarySearchTreeIterTraits<void>::next should not be used.");
  }

};

// Returns as iterator to traverse the tree in pre order
class Traits_PreOrder;
template<class T> class BinarySearchTreeIterTraits<T, Traits_PreOrder>
{
public:
  static typename BinarySearchTree<T>::Node* next(std::stack<typename BinarySearchTree<T>::Node*> &stack,
                                                  std::queue<typename BinarySearchTree<T>::Node*> &queue,
                                                  typename BinarySearchTree<T>::Node* trav) {
    std::cout << "next BinarySearchTreeIterTraits<Traits_PreOrder>" << std::endl;
    typename BinarySearchTree<T>::Node *node = nullptr;
    if (!stack.empty()) {
//      std::cout << "next BinarySearchTreeIterTraits<Traits_PreOrder> stack not empty" << std::endl;
      node = stack.top(); stack.pop();
      if (node->Right() != nullptr) stack.push(node->Right());
      if (node->Left() != nullptr) stack.push(node->Left());
    }

//    if (node!= nullptr) std::cout << "next BinarySearchTreeIterTraits<Traits_PreOrder> node:" << node->Data() << std::endl;

    return node;
  }
};


// Returns as iterator to traverse the tree in order
class Traits_InOrder;
template<class T> class BinarySearchTreeIterTraits<T, Traits_InOrder>
{
public:
  static typename BinarySearchTree<T>::Node* next(std::stack<typename BinarySearchTree<T>::Node*> &stack,
                                                  std::queue<typename BinarySearchTree<T>::Node*> &queue,
                                                  typename BinarySearchTree<T>::Node* trav) {
    std::cout << "next BinarySearchTreeIterTraits<Traits_InOrder>" << std::endl;
    typename BinarySearchTree<T>::Node *node = nullptr;
    // Dig left
    while (trav != nullptr) {
      if (trav->Left() == nullptr) break;
      stack.push(trav->Left());
      trav = trav->Left();
    }

    if (!stack.empty()) {
      node = stack.top(); stack.pop();
    }

    // Try moving down right once
    if (node != nullptr) {
      if (node->Right() != nullptr) {
        stack.push(node->Right());
        trav = node->Right();
      }
    }

    return node;
  }
};


// Returns as iterator to traverse the tree in post order
class Traits_PostOrder;
template<class T> class BinarySearchTreeIterTraits<T, Traits_PostOrder>
{
public:
  static typename BinarySearchTree<T>::Node* next(std::stack<typename BinarySearchTree<T>::Node*> &stack,
                                                  std::queue<typename BinarySearchTree<T>::Node*> &queue,
                                                  typename BinarySearchTree<T>::Node* trav) {
    std::cout << "next BinarySearchTreeIterTraits<Traits_PostOrder>" << std::endl;
    typename BinarySearchTree<T>::Node *node = nullptr;
    if (!stack.empty()) {
      node = stack.top(); stack.pop();
    }
    return node;
  }
};


// Returns as iterator to traverse the tree in level order
class Traits_LevelOrder;
template<class T> class BinarySearchTreeIterTraits<T, Traits_LevelOrder>
{
public:
  static typename BinarySearchTree<T>::Node* next(std::stack<typename BinarySearchTree<T>::Node*> &stack,
                                                  std::queue<typename BinarySearchTree<T>::Node*> &queue,
                                                  typename BinarySearchTree<T>::Node* trav) {
    std::cout << "next BinarySearchTreeIterTraits<Traits_LevelOrder>" << std::endl;
    typename BinarySearchTree<T>::Node *node = nullptr;

    if (!queue.empty()) {
      node = queue.front(); queue.pop();
      if (node->Left() != nullptr) queue.push(node->Left());
      if (node->Right() != nullptr) queue.push(node->Right());
    }

    return node;
  }
};


// This class implements a multiple C++ iterator for a given TreeTraversalOrder.
// The ways in which you can traverse the tree are in four different ways:
// preorder, inorder, postorder and levelorder.
template <class T, typename TRTS, typename Traits = BinarySearchTreeIterTraits<T, TRTS>>
class BinarySearchTreeIter: public std::iterator< std::forward_iterator_tag, std::string >
{
public:

  // Constructors
  BinarySearchTreeIter(BinarySearchTree<T>* parent, typename BinarySearchTree<T>::Node* start)
  	: parent_(parent),
	  expectedNodeCount_(parent->size()),
	  node_(nullptr),
	  trav_(start)
  {
    if (start != nullptr) {
      std::cout << "xtor non NULL BinarySearchTreeIter" << std::endl;
      if (std::is_same<TRTS, void>::value) {
        std::cout << "xtor void BinarySearchTreeIter" << std::endl;
        stack_.push(start);
      }

      if (std::is_same<TRTS, Traits_PreOrder>::value) {
        std::cout << "xtor Traits_PreOrder BinarySearchTreeIter" << std::endl;
        stack_.push(start);
      }

      if (std::is_same<TRTS, Traits_PostOrder>::value) {
        std::cout << "xtor Traits_PostOrder BinarySearchTreeIter" << std::endl;
        std::stack<typename BinarySearchTree<T>::Node*> stack;
        stack.push(start);
        while (!stack.empty()) {
          typename BinarySearchTree<T>::Node *node = stack.top(); stack.pop();
          if (node != nullptr) {
            stack_.push(node);
            if (node->Left() != nullptr) stack.push(node->Left());
            if (node->Right() != nullptr) stack.push(node->Right());
          }
        }
      }

      if (std::is_same<TRTS, Traits_LevelOrder>::value) {
        std::cout << "xtor Traits_LevelOrder BinarySearchTreeIter" << std::endl;
        queue_.push(start);
      }

      node_ = Traits::next(stack_, queue_, trav_);
    }
//    std::cout << "xtor NULL BinarySearchTreeIter" << std::endl;
  }

  // Copy constructor
  BinarySearchTreeIter(const BinarySearchTreeIter<T, void> &other) {
    std::cout << "copy xtor BinarySearchTreeIter" << std::endl;
    parent_ = other.parent_;
    expectedNodeCount_ = other.expectedNodeCount_;
    node_ = other.node_;
    trav_ = other.trav_;
  }

  // Operators
  const T operator*() const {
//    std::cout << "operator*" << std::endl;
    if (expectedNodeCount_ != parent_->size()) throw std::runtime_error("Concurrent Modification Exception");
    if (node_ == nullptr) throw std::runtime_error("NULL Tree");
    return node_->Data();
  }

  BinarySearchTreeIter& operator++() {
    // The contents of the table have been altered
//    std::cout << "operator++: expectedNodeCount_:" << expectedNodeCount_ << " nodeCount_:" << parent_->size() << std::endl;
    if (expectedNodeCount_ != parent_->size()) throw std::runtime_error("Concurrent Modification Exception");
    node_ = Traits::next(stack_, queue_, trav_);
    return *this;
  }

  BinarySearchTreeIter & operator++(int) {
    // The contents of the table have been altered
    if (expectedNodeCount_ != parent_->size()) throw std::runtime_error("Concurrent Modification Exception");
    node_ = Traits::next(stack_, queue_, trav_);
    return *this;
  }


  // ToDo: stck and queue must be copied!
  BinarySearchTreeIter operator=(BinarySearchTreeIter<T, void> val)	{
    parent_ = val.parent_;
    expectedNodeCount_ = val.expectedNodeCount_;
    node_ = val.node_;
    trav_ = val.trav_;
  	return *this;
  }


  template <class U, typename N>
  bool operator==(const BinarySearchTreeIter<U, N>& other) {
//    std::cout << "operator==" << std::endl;
//    if (other.node_ == nullptr) std::cout << "other.node_ is NULL" << std::endl;
//    if (node_ == nullptr) std::cout << "node_ is NULL" << std::endl;
    return node_ == other.node_;
  }

  template <class Y, typename X>
  bool operator!=(const BinarySearchTreeIter<Y, X>& other) {
    return !((*this) == other);
  }

private:

  BinarySearchTree<T>* parent_;
  int expectedNodeCount_;
  std::stack<typename BinarySearchTree<T>::Node*> stack_;
  std::queue<typename BinarySearchTree<T>::Node*> queue_;
  typename BinarySearchTree<T>::Node *node_;
  typename BinarySearchTree<T>::Node* trav_;

  friend class BinarySearchTreeIter<T, Traits_PreOrder>;
  friend class BinarySearchTreeIter<T, Traits_InOrder>;
  friend class BinarySearchTreeIter<T, Traits_PostOrder>;
  friend class BinarySearchTreeIter<T, Traits_LevelOrder>;

};


template <class T>
class BinarySearchTree {

public:
  // Internal node containing node references
  // and the actual node data
  class Node {
  private:
    T data_;
    Node *left_, *right_;
    friend class BinarySearchTree<T>;

  public:
    Node(Node *left, Node *right, T elem) : data_(elem),
                                            left_(left),
                                            right_(right) {}

    bool operator!=(const Node& node) {
    	std::cout << "node !=" << std::endl;
      return data_ != node.data_ || left_ != node.left_ || right_ != node.right_;
    }


    Node* Left() { return left_; }
    Node* Right() { return right_;}
    T Data() { return data_;}

    std::string toString() const {
  	std::stringstream os;
      os << "Node(" << data_ << ")";
      return os.str();
    }

    friend std::ostream& operator<<(std::ostream &strm, const Node &a) {
      return strm << a.toString();
    }

  };

private:

   template<typename TRAITS> class TraversalIterator
   {
   public:

     TraversalIterator(BinarySearchTree* parent) noexcept :
       parent_(parent) {
     }

     BinarySearchTreeIter<T, TRAITS> begin() {
       BinarySearchTreeIter<T, TRAITS> tmp(parent_, parent_->root_);
       return tmp;
     }

     BinarySearchTreeIter<T, TRAITS> end() {
       BinarySearchTreeIter<T, TRAITS> tmp(parent_, nullptr);
       return tmp;
     }
   private:

     BinarySearchTree* parent_;
   };

private:
  // Tracks the number of nodes in this BST
  int nodeCount_;

  // This BST is a rooted tree so we maintain a handle on the root node
  Node *root_;

  TraversalIterator<Traits_PreOrder> preorder_iterator_;
  TraversalIterator<Traits_InOrder> inorder_iterator_;
  TraversalIterator<Traits_PostOrder> postorder_iterator_;
  TraversalIterator<Traits_LevelOrder> levelorder_iterator_;

public:

  TraversalIterator<Traits_PreOrder>   preorder_iter()   { return preorder_iterator_; }
  TraversalIterator<Traits_InOrder>    inorder_iter()    { return inorder_iterator_; }
  TraversalIterator<Traits_PostOrder>  postorder_iter()  { return postorder_iterator_; }
  TraversalIterator<Traits_LevelOrder> levelorder_iter() { return levelorder_iterator_; }


  typedef BinarySearchTreeIter<T, Traits_PreOrder>   PREORDER_ITER;
  typedef BinarySearchTreeIter<T, Traits_InOrder>    INORDER_ITER;
  typedef BinarySearchTreeIter<T, Traits_PostOrder>  POSTORDER_ITER;
  typedef BinarySearchTreeIter<T, Traits_LevelOrder> LEVELORDER_ITER;


public:
  BinarySearchTree() : nodeCount_(0),
                       root_(nullptr),
					   preorder_iterator_(TraversalIterator<Traits_PreOrder>(this)),
					   inorder_iterator_ (TraversalIterator<Traits_InOrder>(this)),
					   postorder_iterator_(TraversalIterator<Traits_PostOrder>(this)),
					   levelorder_iterator_ (TraversalIterator<Traits_LevelOrder>(this))
{
  }

  // ToDo: Nodes must be cleanly deleted!
  ~BinarySearchTree() {
    if (root_) delete root_;
    root_ = nullptr;
  }


  // Check if this binary tree is empty
  bool isEmpty() const {
    return size() == 0;
  }


  // Get the number of nodes in this binary tree
  int size() const {
    return nodeCount_;
  }


  // Add an element to this binary tree. Returns true
  // if we successfully perform an insertion
  bool add(const T &elem) {

    // Check if the value already exists in this
    // binary tree, if it does ignore adding it
    if (contains(elem)) {
      return false;

      // Otherwise add this element to the binary tree
    } else {
      root_ = add(root_, elem);
      nodeCount_++;
      return true;
    }
  }

private:
  // Private method to recursively add a value in the binary tree
  Node* add(Node *node, const T &elem) {

    // Base case: found a leaf nodes
    if (node == nullptr) {
      node = new Node(nullptr, nullptr, elem);

    } else {
      // Pick a subtree to insert element
      if (elem < node->data_) {
        node->left_ = add(node->left_, elem);
      } else {
        node->right_ = add(node->right_, elem);
      }
    }

    return node;
  }

public:
  // Remove a value from this binary tree if it exists, O(n)
  bool remove(const T &elem) {

    // Make sure the node we want to remove
    // actually exists before we remove it
    if (contains(elem)) {
      root_ = remove(root_, elem);
      nodeCount_--;
      return true;
    }
    return false;
  }

private:
   Node *remove(Node *node, const T &elem) {

    if (node == nullptr) return nullptr;

    // Dig into left subtree, the value we're looking
    // for is smaller than the current value
    if (elem < node->data_) {
      node->left_ = remove(node->left_, elem);

      // Dig into right subtree, the value we're looking
      // for is greater than the current value
    } else if (elem > node->data_) {
      node->right_ = remove(node->right_, elem);

      // Found the node we wish to remove
    } else {

      // This is the case with only a right subtree or
      // no subtree at all. In this situation just
      // swap the node we wish to remove with its right child.
      if (node->left_ == nullptr) {

        Node *rightChild = node->right_;

        delete node;
//        node->data_ = nullptr;
        node = nullptr;

        return rightChild;

        // This is the case with only a left subtree or
        // no subtree at all. In this situation just
        // swap the node we wish to remove with its left child.
      } else if (node->right_ == nullptr) {

        Node *leftChild = node->left_;

        delete node;
//        node->data_ = nullptr;
        node = nullptr;

        return leftChild;

        // When removing a node from a binary tree with two links the
        // successor of the node being removed can either be the largest
        // value in the left subtree or the smallest value in the right
        // subtree. In this implementation I have decided to find the
        // smallest value in the right subtree which can be found by
        // traversing as far left as possible in the right subtree.
      } else {

        // Find the leftmost node in the right subtree
        Node *tmp = findMin(node->right_);

        // Swap the data
        node->data_ = tmp->data_;

        // Go into the right subtree and remove the leftmost node we
        // found and swapped data with. This prevents us from having
        // two nodes in our tree with the same value.
        node->right_ = remove(node->right_, tmp->data_);

        // If instead we wanted to find the largest node in the left
        // subtree as opposed to smallest node in the right subtree
        // here is what we would do:
        // Node tmp = findMax(node.left);
        // node.data_ = tmp.data_;
        // node.left = remove(node.left, tmp.data_);

      }
    }

    return node;
  }

private:
  // Helper method to find the leftmost node (which has the smallest value)
  Node *findMin(Node *node) {
    while (node->left_ != nullptr) node = node->left_;
    return node;
  }

  // Helper method to find the rightmost node (which has the largest value)
  Node *findMax(Node *node) {
    while (node->right_ != nullptr) node = node->right_;
    return node;
  }

public:
  // returns true is the element exists in the tree
  bool contains(const T &elem) {
    return contains(root_, elem);
  }

private:
  // private recursive method to find an element in the tree
  bool contains(Node *node, const T &elem) {

    // Base case: reached bottom, value not found
    if (node == nullptr) return false;

    // Dig into the left subtree because the value we're
    // looking for is smaller than the current value
    if (elem < node->data_) return contains(node->left_, elem);

    // Dig into the right subtree because the value we're
    // looking for is greater than the current value
    else if (elem > node->data_) return contains(node->right_, elem);

    // We found the value we were looking for
    else return true;
  }


public:
  // Computes the height of the tree, O(n)
  int height() {
    return height(root_);
  }

private:
  // Recursive helper method to compute the height of the tree
   int height(Node *node) {
    if (node == nullptr) return 0;
    return std::max(height(node->left_), height(node->right_)) + 1;
  }

public:

};

} // namespace dsa

#endif /* D_BINARYSEARCHTREE_H */
