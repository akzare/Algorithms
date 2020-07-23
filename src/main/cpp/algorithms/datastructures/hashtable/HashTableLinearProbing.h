/*
 * @file   HashTableLinearProbing.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   14 July 2020
 * @version 0.1
 * @brief   An implementation of a hash-table using open addressing with linear probing as a collision
 * resolution method.
 */

#ifndef D_HASHTABLELINEARPROBING_H
#define D_HASHTABLELINEARPROBING_H

#include <HashTableOpenAddressingBase.h>

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
#include <cmath>

namespace dsa {


template <class KEY, class VALUE>
class HashTableLinearProbing : public HashTableOpenAddressingBase<KEY, VALUE> {
private:

public:
  HashTableLinearProbing() : HashTableOpenAddressingBase<KEY, VALUE>() {}

  HashTableLinearProbing(int capacity) : HashTableOpenAddressingBase<KEY, VALUE>(capacity) {}

  HashTableLinearProbing(int capacity, double loadFactor) : HashTableOpenAddressingBase<KEY, VALUE>(capacity, loadFactor) {}

protected:
};


} // namespace dsa

#endif /* D_HASHTABLELINEARPROBING_H */
