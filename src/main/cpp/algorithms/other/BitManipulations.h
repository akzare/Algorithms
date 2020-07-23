/*
 * @file   BitManipulations.h
 * @author (original JAVA) Micah Stairs
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   13 July 2020
 * @version 0.1
 * @brief   Fundamental bit manipulation operations you must know Time Complexity: O(1).
 */

#ifndef D_BITMANIPULATIONS_H
#define D_BITMANIPULATIONS_H

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

class BitManipulations {
public:
  BitManipulations(const BitManipulations&) = delete;
  BitManipulations& operator=(BitManipulations const&) = delete;

  // Sets the i'th bit to 1
  static int setBit(int set, int i) {
    return set | (1 << i);
  }


  // Checks if the i'th is set
  static bool isSet(int set, int i) {
    return (set & (1 << i)) != 0;
  }


  // Sets the i'th bit to zero
  static int clearBit(int set, int i) {
    return set & ~(1 << i);
  }


  // Toggles the i'th bit from 0 -> 1 or 1 -> 0
  static int toggleBit(int set, int i) {
    return set ^ (1 << i);
  }


  // Returns a number with the first n bits set to 1
  static int setAll(int n) {
    return (1 << n) - 1;
  }


  // Verifies if a number n is a power of two
  static bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
  }
};

} // namespace dsa

#endif /* D_BITMANIPULATIONS_H */
