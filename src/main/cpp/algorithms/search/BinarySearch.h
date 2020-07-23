/*
 * @file   BinarySearch.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   13 July 2020
 * @version 0.1
 * @brief   Binary search implementation.
 * In the event that you need to do a binary search on the real numbers
 * you can resort to this implementation.
 *
 * <p>Time Complexity: O(log(high-low))
 */

#ifndef D_BINARYSEARCH_H
#define D_BINARYSEARCH_H

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

class BinarySearch {

  // Comparing double values directly is bad practice.
  // Using a small epsilon value is the preferred approach

public:
  static double binarySearch(double lo, double hi, double target, std::function<double (double)> func) {
//	const double EPS = std::numeric_limits<double>::epsilon();
	const double EPS = 0.00000001;

    if (hi <= lo) std::invalid_argument("hi should be greater than lo");

    double mid;
    do {

      // Find the middle point
      mid = (hi + lo) / 2.0;

      // Compute the value of our function for the middle point
      // Note that f can be any function not just the square root function
      double value = func(mid);
//      std::cout << "mid:" << mid << " val:" << value << " target:" << target << " hi:" << hi << " lo:" << lo << " dif:" << (hi - lo) << " eps:" << EPS << std::endl;

      if (value > target) {
        hi = mid;
      } else {
        lo = mid;
      }

    } while ((hi - lo) > EPS);

    return mid;
  }


  // A recursive binary search function. It returns
  // location of x in given array arr[l..r] is present,
  // otherwise -1
  static int binarySearchRecur(const std::vector<int>& arr, int l, int r, int x)
  {
    if (r <= l) std::invalid_argument("right should be greater than left");
    if (r >= l) {
      int mid = l + (r - l) / 2;

      // If the element is present at the middle
      // itself
      if (arr[mid] == x)
        return mid;

      // If element is smaller than mid, then
      // it can only be present in left subarray
      if (arr[mid] > x)
        return binarySearchRecur(arr, l, mid - 1, x);

      // Else the element can only be present
      // in right subarray
      return binarySearchRecur(arr, mid + 1, r, x);
    }

    // We reach here when element is not
    // present in array
    return -1;
  }



  // A iterative binary search function. It returns
  // location of x in given array arr[l..r] if present,
  // otherwise -1
  static int binarySearchIter(const std::vector<int>& arr, int l, int r, int x)
  {
    if (r <= l) throw std::invalid_argument("right should be greater than left");
    while (l <= r) {
      int m = l + (r - l) / 2;

      // Check if x is present at mid
      if (arr[m] == x)
        return m;

      // If x greater, ignore left half
      if (arr[m] < x)
        l = m + 1;

      // If x is smaller, ignore right half
      else
        r = m - 1;
    }

    // if we reach here, then element was
    // not present
    return -1;
  }

};



// Example usage of Binary search
int BinarySearch_test()
{

  // EXAMPLE #1
  // Suppose we want to know what the square root of 875 is and
  // we have no knowledge of the wonderful Math.sqrt() function.
  // One approach is to use a binary search because we know that
  // the square root of 875 is bounded in the region: [0, 875].
  //
  // We can define our function to be f(x) = x*x and our target
  // value to be 875. As we binary search on f(x) approaching
  // successively closer values of 875 we get better and better
  // values of x (the square root of 875=29.5804)

  double lo = 0.0;
  double hi = 875.0;
  double target = 875.0;

  auto function = [](double x) -> double { return x * x; };
  double sqrtVal = BinarySearch::binarySearch(lo, hi, target, function);
  std::cout << "sqrt(" << target  << ") = " << sqrtVal << ", x^2 = " << (sqrtVal * sqrtVal) << std::endl;

  // EXAMPLE #2
  // Suppose we want to find the radius of a sphere with volume 100m^3 using
  // a binary search(r=2.87941). We know that for a sphere the volume is given by
  // V = (4/3)*pi*r^3, so all we have to do is binary search on the radius.
  //
  // Note: this is a silly example because you could just solve for r, but it
  // shows how binary search can be a powerful technique.

  double radiusLowerBound = 0;
  double radiusUpperBound = 1000;
  double volume = 100.0;

  auto sphereVolumeFunction = [](double r) -> double { return (4.0 / 3.0) * M_PI * r * r * r; };
  double sphereRadius =
		  BinarySearch::binarySearch(radiusLowerBound, radiusUpperBound, volume, sphereVolumeFunction);

  std::cout << "Sphere radius = " << sphereRadius << std::endl;


  std::vector<int> arr{ 2, 3, 4, 10, 40 };
  int x = 10;
  int n = arr.size();
  int result = BinarySearch::binarySearchRecur(arr, 0, n - 1, x);
  (result == -1) ? std::cout << "binarySearchRecur : Element is not present in array"
                 : std::cout << "binarySearchRecur : Element is present at index " << result << std::endl;

  result = BinarySearch::binarySearchIter(arr, 0, n - 1, x);
  (result == -1) ? std::cout << "BinarySearchIter : Element is not present in array"
                 : std::cout << "BinarySearchIter : Element is present at index " << result << std::endl;

  return 0;
}


} // namespace dsa

#endif /* D_BUCKETSORT_H */
