/*
 * @file   LCM.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   15 July 2020
 * @version 0.1
 * @brief   An implementation of finding the LCM of two numbers
 *
 * <p>Time Complexity ~O(log(a + b))
 */

#ifndef D_LCM_H
#define D_LCM_H

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

class LCM {
private:
  // Finds the greatest common divisor of a and b
  static long gcd(long a, long b) {
    return b == 0 ? (a < 0 ? -a : a) : gcd(b, a % b);
  }

public:
  // Finds the least common multiple of a and b
  static long lcm(long a, long b) {
    long lcm = (a / gcd(a, b)) * b;
    return lcm > 0 ? lcm : -lcm;
  }
};


void LCM_test()
{
  std::cout << LCM::lcm(12, 18) << std::endl; // 36
  std::cout << LCM::lcm(-12, 18) << std::endl; // 36
  std::cout << LCM::lcm(12, -18) << std::endl; // 36
  std::cout << LCM::lcm(-12, -18) << std::endl; // 36
}

} // namespace dsa

#endif /* D_LCM_H */
