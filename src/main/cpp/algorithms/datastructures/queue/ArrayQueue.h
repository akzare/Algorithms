/*
 * @file   ArrayQueue.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *                         liujingkun, liujkon@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   03 July 2020
 * @version 0.1
 * @brief   An array implementation of a queue.
 */

#ifndef D_ARRAY_QUEUE_H
#define D_ARRAY_QUEUE_H

#include <Queue.h>

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
class ArrayQueue : public Queue<T> {
private:
  std::vector<T> data_;
  int front_;
  int rear_;

public:
  ArrayQueue(int id, int capacity) : Queue<T>(id) {
    // ArrayQueue maximum size is data.length - 1.
	data_= std::vector<T>(capacity + 1, 0);
    front_ = 0;
    rear_ = 0;
  }


  ~ArrayQueue() {
    data_.clear();
  }

  void clear() override {
    front_ = 0;
    rear_ = 0;
  }

  void offer(T elem) override {
    if (isFull()) {
      throw std::runtime_error("Queue Full");
    }
    data_[rear_++] = elem;
    rear_ = adjustIndex(rear_, data_.size());
  }


  T poll() override {
    if (isEmpty()) {
      throw std::runtime_error("Queue Empty");
    }

    front_ = adjustIndex(front_, data_.size());
    return (T) data_[front_++];
  }


  T peek() override {
    if (isEmpty()) {
      throw std::runtime_error("Queue Empty");
    }
    front_ = adjustIndex(front_, data_.size());
    return (T) data_[front_];
  }


  int size() override {
    return adjustIndex(rear_ + data_.size() - front_, data_.size());
  }


  bool isEmpty() override {
    return rear_ == front_;
  }

  bool isFull() {
    return (front_ + data_.size() - rear_) % data_.size() == 1;
  }

private:
  int adjustIndex(int index, int size) {
    return index >= size ? index - size : index;
  }
};

} // namespace dsa

#endif /* D_ARRAY_QUEUE_H */
