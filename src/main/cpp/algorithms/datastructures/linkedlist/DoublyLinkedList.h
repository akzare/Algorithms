/*
 * @file   DoublyLinkedList.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   01 July 2020
 * @version 0.1
 * @brief   A doubly linked list implementation.
 */

#ifndef D_LINKLIST_H
#define D_LINKLIST_H

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
#include <stdexcept>

namespace dsa {

// Forward declaration
template <class T>
class DoublyLinkedList;


template <typename T>
class DoublyLinkedList
{
public:
  // Internal node class to represent data
  template <typename U>
  class Node
  {
  private:
    T data_;
    Node<T> *prev_, *next_;

    // DoublyLinkedList class methods need
    // to access Node information
    friend class DoublyLinkedList<T>;

  public:
    Node():prev_(nullptr), next_(nullptr) {
    }

    Node(const T &data, Node<T> *prev, Node<T> *next):data_(data), prev_(prev), next_(next) {
    }

    std::string toString() const {
  	std::stringstream os;
      os << "Node(" << data_ << ")";
      return os.str();
    }

    friend std::ostream& operator<<(std::ostream &strm, const Node<T> &a) {
      return strm << a.toString();
    }

  };

private:

  int size_ = 0;
  Node<T> *head_;
  Node<T> *tail_;

public:

  DoublyLinkedList():size_(0), head_(nullptr), tail_(nullptr) {
  }


  virtual ~DoublyLinkedList() {
    clear();
  }


  // Iterator class can be used to sequentially access nodes of linked list
  class Iterator
  {
  public:
    Iterator() noexcept : currNode_ (head_) { }

    Iterator(const Node<T>* pNode) noexcept : currNode_ (pNode) { }

    Iterator& operator=(Node<T>* pNode)
    {
      this->currNode_ = pNode;
      return *this;
    }

    // Prefix ++ overload
    Iterator& operator++()
    {
      if (currNode_)
        currNode_ = currNode_->next_;
      return *this;
    }

    // Postfix ++ overload
    Iterator operator++(int)
    {
      Iterator iterator = *this;
      ++*this;
      return iterator;
    }

    bool operator!=(const Iterator& iterator)
    {
      return currNode_ != iterator.currNode_;
    }

    T operator*()
    {
      return currNode_->data_;
    }

  private:
    const Node<T>* currNode_;
  };



  // Empty this linked list, O(n)
  void clear() {
    Node<T> *trav = head_;
    while (trav != nullptr) {
      Node<T> *next = trav->next_;
      delete trav;
      trav = nullptr;
      trav = next;
    }
    head_ = nullptr;
    tail_ = nullptr;
    trav = nullptr;
    size_ = 0;
  }


  // Return the size of this linked list
  int size() {
    return size_;
  }


  // Is this linked list empty?
  bool isEmpty() {
    return size() == 0;
  }


  // Add an element to the tail of the linked list, O(1)
  void add(const T &elem) {
    addLast(elem);
  }


  // Add a node to the tail of the linked list, O(1)
  void addLast(const T &elem) {
    if (isEmpty()) {
      head_ = new Node<T>(elem, nullptr, nullptr);
      tail_ = head_;
    } else {
      tail_->next_ = new Node<T>(elem, tail_, nullptr);
      tail_ = tail_->next_;
    }
    size_++;
  }


  // Add an element to the beginning of this linked list, O(1)
  void addFirst(const T &elem) {
    if (isEmpty()) {
      head_ = new Node<T>(elem, nullptr, nullptr);
      tail_ = head_;
    } else {
      head_->prev_ = new Node<T>(elem, nullptr, head_);
      head_ = head_->prev_;
    }
    size_++;
  }


  // Add an element at a specified index
  void addAt(int index, const T &data) {
    if (index < 0) {
      throw ("Illegal Index");
    }
    if (index == 0) {
      addFirst(data);
      return;
    }

    if (index == size_) {
      addLast(data);
      return;
    }

    Node<T> *temp = head_;
    for (int i = 0; i < index - 1; i++) {
      temp = temp->next_;
    }
    Node<T> *newNode = new Node<T>(data, temp, temp->next_);
    temp->next_->prev_ = newNode;
    temp->next_ = newNode;

    size_++;
  }


  // Check the value of the first node if it exists, O(1)
  T peekFirst() {
    if (isEmpty()) throw std::runtime_error("Empty list");
    return head_->data_;
  }


  // Check the value of the last node if it exists, O(1)
  T peekLast() {
    if (isEmpty()) throw std::runtime_error("Empty list");
    return tail_->data_;
  }


  // Remove the first value at the head of the linked list, O(1)
  T removeFirst() {
    // Can't remove data from an empty list
    if (isEmpty()) throw std::runtime_error("Empty list");

    // Extract the data at the head and move
    // the head pointer forwards one node
    T data = head_->data_;
    head_ = head_->next_;
    --size_;

    // If the list is empty set the tail to NULL
    if (isEmpty()) tail_ = nullptr;

    // Do a memory cleanup of the previous node
    else head_->prev_ = nullptr;

    // Return the data that was at the first node we just removed
    return data;
  }


  // Remove the last value at the tail of the linked list, O(1)
  T removeLast() {
    // Can't remove data from an empty list
    if (isEmpty()) throw std::runtime_error("Empty list");

    // Extract the data at the tail and move
    // the tail pointer backwards one node
    T data = tail_->data_;
    tail_ = tail_->prev_;
    --size_;

    // If the list is now empty set the head to NULL
    if (isEmpty()) head_ = nullptr;

    // Do a memory clean of the node that was just removed
    else tail_->next_ = nullptr;

    // Return the data that was in the last node we just removed
    return data;
  }


  // Function to reverse the linked list
  void reverse() {
  {
    // Initialize current, previous and
    // next pointers
    Node<T>* current = head_;
    Node<T> *prev = nullptr, *next = nullptr;

    while (current != nullptr) {
      // Store next
      next = current->next_;

      // Reverse current node's pointer
      current->next_ = prev;

      // Move pointers one position ahead.
      prev = current;
      current = next;
    }
    head_ = prev;
    }

    {
    // Initialize current, previous and
    // next pointers
    Node<T>* current = tail_;
    Node<T> *prev = nullptr, *next = nullptr;

    while (current != nullptr) {
      // Store next
      prev = current->prev_;

      // Reverse current node's pointer
      current->prev_ = next;

      // Move pointers one position ahead.
      next = current;
      current = prev;
    }
    tail_ = next;
    }
  }

private:
  // Remove an arbitrary node from the linked list, O(1)
  T remove_(Node<T> *node) {
    // If the node to remove is somewhere either at the
    // head or the tail handle those independently
    if (node->prev_ == nullptr) return removeFirst();
    if (node->next_ == nullptr) return removeLast();

    // Make the pointers of adjacent nodes skip over 'node'
    node->next_->prev_ = node->prev_;
    node->prev_->next_ = node->next_;

    // Temporarily store the data we want to return
    T data = node->data_;

    // Memory cleanup
//    node->data_ = nullptr;
    node->prev_ = nullptr;
    node->next_ = nullptr;
    node = nullptr;

    --size_;

    // Return the data in the node we just removed
    return data;
  }


public:
  // Remove a node at a particular index, O(n)
  T removeAt(int index) {
    // Make sure the index provided is valid
    if (index < 0 || index >= size_) {
      throw std::invalid_argument("Invalid Index");
    }

    int i;
    Node<T> *trav;

    // Search from the front of the list
    if (index < size_ / 2) {
      for (i = 0, trav = head_; i != index; i++) {
        trav = trav->next_;
      }
    // Search from the back of the list
    } else
      for (i = size_ - 1, trav = tail_; i != index; i--) {
        trav = trav->prev_;
      }

    return remove_(trav);
  }


  // Remove a particular value in the linked list, O(n)
  bool remove(const T &obj) {
    Node<T> *trav = head_;

    for (trav = head_; trav != nullptr; trav = trav->next_) {
      if (obj == trav->data_) {
        remove_(trav);
        return true;
      }
    }
    return false;
  }


  // Find the index of a particular value in the linked list, O(n)
  int indexOf(const T &obj) {
    int index = 0;
    Node<T> *trav = head_;

    for (; trav != nullptr; trav = trav->next_, index++) {
      if (obj == trav->data_) {
        return index;
      }
    }
    return -1;
  }


  // Check is a value is contained within the linked list
  bool contains(const T &obj) {
    return indexOf(obj) != -1;
  }

  // Root of LinkedList wrapped in Iterator type
  Iterator begin()
  {
    return Iterator(head_);
  }

  // End of LInkedList wrapped in Iterator type
  Iterator end()
  {
    return Iterator(nullptr);
  }


  std::string toString() const {
	std::stringstream os;
    os << "[ ";
    Node<T> *trav = head_;
    while (trav != nullptr) {
      os << trav->data_;
      trav = trav->next_;
      if (trav) os << ", ";
    }
    os << " ]";
    return os.str();
  }


  friend std::ostream& operator<<(std::ostream &strm, const DoublyLinkedList<T> &a) {
    return strm << a.toString();
  }

};


} // namespace dsa

#endif /* D_LINKLIST_H */

