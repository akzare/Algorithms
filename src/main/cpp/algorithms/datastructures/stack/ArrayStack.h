/*
 * @file   ArrayStack.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *                         liujingkun
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   03 July 2020
 * @version 0.1
 * @brief   An array implementation of a stack.
 */

#ifndef D_ARRAY_STACK_H
#define D_ARRAY_STACK_H

#include <Stack.h>

#include <deque>
#include <vector>
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
class ArrayStack : public Stack<T> {
private:
  int capacity_;
  std::vector<T> data_;

public:
  ArrayStack(int id) : Stack<T>(id) {
    capacity_ = data_.capacity();
  }

  ~ArrayStack() {
    data_.clear();
  }

  // Clear the stack
  void clear() override {
	data_.clear();
	data_.shrink_to_fit();
	capacity_ = data_.capacity();
  }

  int size() override {
    return data_.size();
  }


  bool isEmpty() override {
    return data_.size() == 0;
  }


  void push(T elem) override {
    data_.push_back(elem);
  }


  T pop() override {
    if (isEmpty()) throw std::runtime_error("Empty Stack");
    T elem = data_.back();
    data_.erase(data_.end()-1);
//    if (data_.capacity() > data_.size()*2)
//      data_.shrink_to_fit();
    return elem;
  }


  T peek() override {
    if (isEmpty()) throw std::runtime_error("Empty Stack");
    return data_.back();
  }
};

} // namespace dsa

#endif /* D_ARRAY_STACK_H */
