/*
 * @file   Queue.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *                         liujingkun, liujkon@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   03 July 2020
 * @version 0.1
 * @brief   An abstract base class for queue.
 */

#ifndef D_QUEUE_H
#define D_QUEUE_H

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
class Queue
{
private:
  int id_;

public:
  Queue(int id) : id_(id) {}

  virtual ~Queue() {}

  virtual void clear() = 0;

  virtual void offer(T elem) = 0;

  virtual T poll() = 0;

  virtual T peek() = 0;

  virtual int size() = 0;

  virtual bool isEmpty() = 0;
};

} // namespace dsa

#endif /* D_QUEUE_H */
