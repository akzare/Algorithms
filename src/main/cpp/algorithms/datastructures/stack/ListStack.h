/*
 * @file   ListStack.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   02 July 2020
 * @version 0.1
 * @brief   A linked list implementation of a stack.
 */


#ifndef D_LINKLIST_STACK_H
#define D_LINKLIST_STACK_H

#include <Stack.h>

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

template <typename T>
class ListStack : public Stack<T> {

private:
  std::list<T> list_;

public:
  // Create an empty stack
  ListStack(int id) : Stack<T>(id) {}

  // Create a Stack with an initial element
  ListStack(int id, T firstElem) : Stack<T>(id) {
    push(firstElem);
  }

  ~ListStack() {
    list_.clear();
  }

  // Iterator class can be used to sequentially access nodes of stack
  class Iterator
  {
  public:

    Iterator() noexcept : it_ (list_.begin()) {
    }

    Iterator& operator=(typename std::list<T>::iterator& it)
    {
      this->it_ = it;
      return *this;
    }

    // Prefix ++ overload
    Iterator& operator++()
    {
      if (it_)
    	  it_++;
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
      return it_ != iterator.it_;
    }

    T operator*()
    {
      return *it_;
    }

  private:
    const typename std::list<T>::iterator it_;
  };

  // Return the number of elements in the stack
  int size() override {
    return list_.size();
  }

  // Clear the stack
  void clear() override {
    list_.clear();
  }

  // Check if the stack is empty
  bool isEmpty() override {
    return size() == 0;
  }

  // Push an element on the stack
  void push(T elem) override {
    list_.push_back(elem);
  }

  // Pop an element off the stack
  // Throws an error is the stack is empty
  T pop() override {
    if (isEmpty()) throw std::runtime_error("Empty Stack");
    T f = list_.back();
    list_.erase(--list_.end());
    return f;
  }

  // Peek the top of the stack without removing an element
  // Throws an exception if the stack is empty
  T peek() override {
    if (isEmpty()) throw std::runtime_error("Empty Stack");
    return list_.back();
  }

};

} // namespace dsa

#endif /* D_LINKLIST_STACK_H */
