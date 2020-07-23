/*
 * @file   GCD.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   15 July 2020
 * @version 0.1
 * @brief   An implementation of finding the GCD of two numbers
 *
 * <p>Time Complexity ~O(log(a + b))
 */

#ifndef D_GCD_H
#define D_GCD_H

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

class GCD {
public:
  // Computes the Greatest Common Divisor (GCD) of a & b
  // This method ensures that the value returned is non negative
  static long gcd(long a, long b) {
    return b == 0 ? (a < 0 ? -a : a) : gcd(b, a % b);
  }
};


void GCD_test()
{
  std::cout << GCD::gcd(12, 18) << std::endl; // 6
  std::cout << GCD::gcd(-12, 18) << std::endl; // 6
  std::cout << GCD::gcd(12, -18) << std::endl; // 6
  std::cout << GCD::gcd(-12, -18) << std::endl; // 6

  std::cout << GCD::gcd(5, 0) << std::endl; // 5
  std::cout << GCD::gcd(0, 5) << std::endl; // 5
  std::cout << GCD::gcd(-5, 0) << std::endl; // 5
  std::cout << GCD::gcd(0, -5) << std::endl; // 5
  std::cout << GCD::gcd(0, 0) << std::endl; // 0
}

} // namespace dsa

#endif /* D_GCD_H */
