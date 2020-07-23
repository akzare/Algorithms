/*
 * @file   TernarySearchDiscrete.h
 * @author (original JAVA) Thomas Finn Lidbetter
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   14 July 2020
 * @version 0.1
 * @brief   An implementation of TernarySearch search.
 * Ternary search is similar to binary search except that it works on a function which decreases and
 * then increases. This implementation of ternary search works on discrete values and returns the
 * input value corresponding with the minimum output value of the function you're searching on.
 *
 * <p>Time Complexity: O(log(high - low)).
 *
 * <p>NOTE: You can also work with a function which increases and then decreases, simply negate your
 * function :)
 */

#ifndef D_TERNARYSEARCHDISCRETE_H
#define D_TERNARYSEARCHDISCRETE_H

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

class TernarySearchDiscrete {

public:
  static double discreteTernarySearch(int lo, int hi, std::function<double (int)> function) {
    // Define a very small epsilon value to compare double values.
    while (lo != hi) {
      if (hi - lo == 1) return std::min(function(lo), function(hi));
      if (hi - lo == 2) return std::min(function(lo), std::min(function(lo + 1), function(hi)));
      int mid1 = (2 * lo + hi) / 3, mid2 = (lo + 2 * hi) / 3;
      double res1 = function(mid1), res2 = function(mid2);
      if (std::abs(res1 - res2) < 0.000000001) {
        lo = mid1;
        hi = mid2;
      } else if (res1 > res2) lo = mid1;
      else hi = mid2;
    }
    return lo;
  }

};


// Example /usage of Ternary search discrete
int TernarySearchDiscrete_test()
{
  // Define your own function on whatever you're attempting to ternary
  // search. Remember that your function must be a discrete and a unimodal
  // function, this means a function which decreases then increases (U shape)
  std::vector<double> func_coe{16, 12, 10, 3, 6, 7, 9, 10, 11, 12, 13, 17};
  auto function = [&func_coe](int i) -> double {
    // A discrete function is just a set of data points.
    return func_coe[i];
  };

  int lo = 0;
  int hi = func_coe.size() - 1;

  // Use ternary search to find the minimum value on the
  // whole interval of out function.
  double minValue = TernarySearchDiscrete::discreteTernarySearch(lo, hi, function);
  std::cout << minValue << std::endl;

  return 0;
}

} // namespace dsa

#endif /* D_TERNARYSEARCHDISCRETE_H */
