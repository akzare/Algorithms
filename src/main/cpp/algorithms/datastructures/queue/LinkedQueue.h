/*
 * @file   LinkedQueue.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   03 July 2020
 * @version 0.1
 * @brief   A simple queue implementation with a linkedlist.
 */


#ifndef D_LINKLIST_QUEUE_H
#define D_LINKLIST_QUEUE_H

#include <Queue.h>

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
class LinkedQueue : public Queue<T> {

private:
  std::list<T> list_;

public:
  // Create an empty stack
  LinkedQueue(int id) : Queue<T>(id) {}

  LinkedQueue(int id, T firstElem) : Queue<T>(id) {
    offer(firstElem);
  }

  ~LinkedQueue() {
    list_.clear();
  }

  // Iterator class can be used to sequentially access nodes of queue
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

  void clear() override {
    list_.clear();
  }

  // Return the size of the queue
  int size() override {
    return list_.size();
  }

  // Returns whether or not the queue is empty
  bool isEmpty() override {
    return size() == 0;
  }

  // Peek the element at the front of the queue
  // The method throws an error is the queue is empty
  T peek() override {
    if (isEmpty()) throw std::runtime_error("Queue Empty");
    return list_.front();
  }

  // Poll an element from the front of the queue
  // The method throws an error if the queue is empty
  T poll() override {
    if (isEmpty()) throw std::runtime_error("Queue Empty");
    T f = list_.front();
    list_.erase(list_.begin());
    return f;
  }

  // Add an element to the back of the queue
  void offer(T elem) override {
    list_.push_back(elem);
  }

};

} // namespace dsa

#endif /* D_LINKLIST_QUEUE_H */
