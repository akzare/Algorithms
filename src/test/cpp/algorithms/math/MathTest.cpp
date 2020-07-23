/*
 * @file   MathTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   15 July 2020
 * @version 0.1
 * @brief   Math Unit Test.
 */

#include <gtest\gtest.h>
#include <GCD.h>
#include <IsPrime.h>
#include <LCM.h>
#include <PrimeFactorization.h>

#include <chrono>
#include <random>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>
#include <array>

namespace dsa {

namespace math {

TEST(MathTest, testGCD) {
  EXPECT_EQ(GCD::gcd(12, 18), 6); // 6
  EXPECT_EQ(GCD::gcd(-12, 18), 6); // 6
  EXPECT_EQ(GCD::gcd(12, -18), 6); // 6
  EXPECT_EQ(GCD::gcd(-12, -18), 6); // 6

  EXPECT_EQ(GCD::gcd(5, 0), 5); // 5
  EXPECT_EQ(GCD::gcd(0, 5), 5); // 5
  EXPECT_EQ(GCD::gcd(-5, 0), 5); // 5
  EXPECT_EQ(GCD::gcd(0, -5), 5); // 5
  EXPECT_EQ(GCD::gcd(0, 0), 0); // 0
}


TEST(MathTest, testisPrime) {
  EXPECT_TRUE(IsPrime::isPrime(5));
  EXPECT_TRUE(IsPrime::isPrime(31));
  EXPECT_TRUE(IsPrime::isPrime(1433));
//  std::cout << IsPrime::isPrime(876385777553687833L) << std::endl;
}


TEST(MathTest, testLCM) {
  EXPECT_EQ(LCM::lcm(12, 18), 36); // 36
  EXPECT_EQ(LCM::lcm(-12, 18), 36); // 36
  EXPECT_EQ(LCM::lcm(12, -18), 36); // 36
  EXPECT_EQ(LCM::lcm(-12, -18), 36); // 36
}


TEST(PrimeFactorizationTest, testPF) {
#define PRINT_FACTORIZATION(r) \
  do { \
	std::cout << "["; \
	for (auto pf : PrimeFactorization::primeFactorization(r)) std::cout << pf << ","; \
	std::cout << "]"; \
  } while(0)

  {
//  PRINT_FACTORIZATION(7); // [7]
  const std::multiset<long> v{7};
  EXPECT_EQ(PrimeFactorization::primeFactorization(7), v);
  }

  {
//  PRINT_FACTORIZATION(100); // [2,2,5,5]
  const std::multiset<long> v{2,2,5,5};
  EXPECT_EQ(PrimeFactorization::primeFactorization(100), v);
  }

  {
//  PRINT_FACTORIZATION(666); // [2,3,3,37]
  const std::multiset<long> v{2,3,3,37};
  EXPECT_EQ(PrimeFactorization::primeFactorization(666), v);
  }

  {
//  PRINT_FACTORIZATION(872342345); // [5, 7, 7, 67, 19, 2797]
  const std::multiset<long> v{5,7,7,67,19,2797};
  EXPECT_EQ(PrimeFactorization::primeFactorization(872342345), v);
  }
}

} // namespace math

} // namespace dsa
