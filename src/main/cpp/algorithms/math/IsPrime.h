/*
 * @file   IsPrime.h
 * @author (original JAVA) Micah Stairs, William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   15 July 2020
 * @version 0.1
 * @brief   Tests whether a number is a prime number or not Time Complexity: O(sqrt(n))
 */

#ifndef D_ISPRIME_H
#define D_ISPRIME_H

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

class IsPrime {
public:
  static bool isPrime(long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    long limit = (long) sqrt(n);

    for (long i = 5; i <= limit; i += 6) {
      if (n % i == 0 || n % (i + 2) == 0) {
        return false;
      }
    }
    return true;
  }

};


void IsPrime_test()
{
  std::cout << IsPrime::isPrime(5) << std::endl;
  std::cout << IsPrime::isPrime(31) << std::endl;
  std::cout << IsPrime::isPrime(1433) << std::endl;
  std::cout << IsPrime::isPrime(8763857775536878331L) << std::endl;
}

} // namespace dsa

#endif /* D_ISPRIME_H */
