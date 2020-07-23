/*
 * @file   TernarySearch.h
 * @author (original JAVA) Micah Stairs
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   14 July 2020
 * @version 0.1
 * @brief   An implementation of TernarySearch search.
 * Ternary search is similar to binary search except that it works on a function which decreases and
 * then increases. This implementation of ternary search returns the input value corresponding with
 * the minimum output value of the function you're searching on.
 *
 * <p>Time Complexity: O(log(high - low)).
 *
 * <p>NOTE: You can also work with a function which increases and then decreases, simply negate your
 * function :)
 */

#ifndef D_TERNARYSEARCH_H
#define D_TERNARYSEARCH_H

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

class TernarySearch {

public:
  // Perform a ternary search on the interval low to high.
  // Remember that your function must be a continuous unimodal
  // function, this means a function which decreases then increases (U shape)
  static double ternarySearch(double low, double high, std::function<double (double)> function) {
    // Define a very small epsilon value to compare double values
    const double EPS = 0.000000001;
    double best = std::numeric_limits<double>::quiet_NaN();
    while (true) {
      double mid1 = (2 * low + high) / 3, mid2 = (low + 2 * high) / 3;
      double res1 = function(mid1), res2 = function(mid2);
      if (res1 > res2) low = mid1;
      else high = mid2;
      if (!std::isnan(best) && std::abs(best - mid1) < EPS) break;
      best = mid1;
    }
    return best;
  }

};


// Example /usage of Ternary search
int TernarySearch_test()
{
  // Search for the lowest point on the function x^2 + 3x + 5
  // using a ternary search on the interval [-100, +100]
  auto function = [](double x) -> double { return x * x + 3 * x + 5; };
  double root = TernarySearch::ternarySearch(-100.0, +100.0, function);
  std::cout << root << std::endl;
  return 0;
}

} // namespace dsa

#endif /* D_TERNARYSEARCH_H */
