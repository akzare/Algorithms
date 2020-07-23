/*
 * @file   PrimeFactorization.h
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   15 July 2020
 * @version 0.1
 * @brief   An implementation of finding the LCM of two numbers
 *
 */

#ifndef D_PRIMEFACTORIZATION_H
#define D_PRIMEFACTORIZATION_H

#include <vector>
#include <deque>
#include <queue>
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

#include <chrono>
#include <random>
#include <sstream>
#include <memory>
#include <iostream>
#include <cmath>

namespace dsa {


class PrimeFactorization {

public:
  static std::multiset<long> primeFactorization(long n) {
	std::multiset<long> factors;
    if (n <= 0) throw std::invalid_argument("Invalid input");
    else if (n == 1) return factors;
    auto longComparer = [](long a, long b) -> bool { return a > b; };
    std::priority_queue<long, std::vector<long>, decltype(longComparer)> divisorQueue(longComparer);
    divisorQueue.push(n);
    while (divisorQueue.size() > 0) {
      long divisor = divisorQueue.top();
      divisorQueue.pop();
      if (isPrime(divisor)) {
        factors.insert(divisor);
        continue;
      }
      long next_divisor = pollardRho(divisor);
      if (next_divisor == divisor) {
        divisorQueue.push(divisor);
      } else {
        divisorQueue.push(next_divisor);
        divisorQueue.push(divisor / next_divisor);
      }
    }
    return factors;
  }

private:

  static int genRandInt(int start_in, int end_in)
  {
    // engine only provides a source of randomness
    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);
    std::uniform_int_distribution<int> dist(start_in, end_in);

    return dist(rng);
  }


  static long pollardRho(long n) {
    if (n % 2 == 0) return 2;
    long x = 2 + (long) genRandInt(0, 999999);
    long c = 2 + (long) genRandInt(0, 999999);
    long y = x;
    long d = 1;
    while (d == 1) {
      x = (x * x + c) % n;
      y = (y * y + c) % n;
      y = (y * y + c) % n;
      d = gcd(abs(x - y), n);
      if (d == n) break;
    }
    return d;
  }


  static long gcd(long a, long b) {
    return b == 0 ? a : gcd(b, a % b);
  }


  static bool isPrime(long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    long limit = (long) sqrt(n);
    for (long i = 5; i <= limit; i += 6) if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
  }

};


void PrimeFactorization_test()
{
#define PRINT_FACTORIZATION(r) \
  do { \
	std::cout << "["; \
	for (auto pf : PrimeFactorization::primeFactorization(r)) std::cout << pf << ","; \
	std::cout << "]"; \
  } while(0)

  PRINT_FACTORIZATION(7); // [7]
  PRINT_FACTORIZATION(100); // [2,2,5,5]
  PRINT_FACTORIZATION(666); // [2,3,3,37]
  PRINT_FACTORIZATION(872342345); // [5, 7, 7, 67, 19, 2797]
}

} // namespace dsa

#endif /* D_PRIMEFACTORIZATION_H */
