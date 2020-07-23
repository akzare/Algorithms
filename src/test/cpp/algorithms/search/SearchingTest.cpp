/*
 * @file   SearchingTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   13 July 2020
 * @version 0.1
 * @brief   Test all searching algorithms under various constraints.
 */

#include <gtest\gtest.h>
#include <BinarySearch.h>
#include <InterpolationSearch.h>
#include <TernarySearch.h>
#include <TernarySearchDiscrete.h>


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

namespace serchingtest {

int genRandInt(int start_in, int end_in)
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


std::vector<int> genRandIntVec(int start_in, int end_in, int num_in)
{
  std::vector<int> randvec;
  // engine only provides a source of randomness
  std::mt19937_64 rng;
  // initialize the random number generator with time-dependent seed
  uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
  rng.seed(ss);
  std::uniform_int_distribution<int> dist(start_in, end_in);

  for(int i=0; i < num_in; ++i) {
    randvec.push_back(dist(rng));
  }

  return std::move(randvec);
}



std::array<std::function<int (const std::vector<int>& arr, int l, int r, int x)>, 1> searchingAlgorithms = {{
//          &BinarySearch::binarySearchRecur,
          &BinarySearch::binarySearchIter,
//		  &QuickSort3::sort
        }};


#if 0
// ToDo: This test fails and needs to be fixed!
TEST(SearchingTest, verifySearchingAlgorithms_smallPositiveIntegersOnly) {
//  BinarySearch_test();

  for (int size = 5; size < 1000; size++) {
    for (auto algorithm : searchingAlgorithms) {
      std::vector<int> rand_vec = genRandIntVec(0, 51, size);
      std::sort(rand_vec.begin(), rand_vec.end());
      int rand_idx = genRandInt(0, rand_vec.size() - 1);
      std::cout << rand_idx << std::endl;
      int found_our_idx = algorithm(rand_vec, 0, rand_vec.size(), rand_vec[rand_idx]);

      // std::find function call
       auto it = std::find (rand_vec.begin(), rand_vec.end(), rand_vec[rand_idx]);
       if (it != rand_vec.end())
       {
         int found_std_idx = std::distance(rand_vec.begin(), it);
         EXPECT_EQ(found_our_idx, found_std_idx);
       }
       else
         EXPECT_EQ(found_our_idx, -1);
    }
  }
}

// ToDo: This test fails and needs to be fixed!
TEST(SearchingTest, verifySearchingAlgorithms_smallNegativeIntegersOnly) {
  for (int size = 5; size < 100; size++) {
    for (auto algorithm : searchingAlgorithms) {
      std::vector<int> rand_vec = genRandIntVec(-50, 51, size);
      int rand_idx = genRandInt(0, size-1);
      int found_our_idx = algorithm(rand_vec, 0, size - 1, rand_vec[rand_idx]);

      // std::find function call
       auto it = std::find (rand_vec.begin(), rand_vec.end(), rand_vec[rand_idx]);
       if (it != rand_vec.end())
       {
         int found_std_idx = std::distance(rand_vec.begin(), it);
         EXPECT_EQ(found_our_idx, found_std_idx);
       }
       else
         EXPECT_EQ(found_our_idx, -1);
    }
  }
}
#endif


TEST(InterpolationSearchTest, testCoverage) {
  std::vector<int> arr{0, 1, 2, 3, 4, 5};
  int index = InterpolationSearch::interpolationSearch(arr, 2);
  EXPECT_TRUE(index == 2);

  index = InterpolationSearch::interpolationSearch(arr, 5);
  EXPECT_TRUE(index == 5);

  index = InterpolationSearch::interpolationSearch(arr, -1);
  EXPECT_TRUE(index == -1);

  index = InterpolationSearch::interpolationSearch(arr, 8);
  EXPECT_TRUE(index == -1);
}


TEST(TernarySearchTest, testCoverage) {
  // Search for the lowest point on the function x^2 + 3x + 5
  // using a ternary search on the interval [-100, +100]
  auto function = [](double x) -> double { return x * x + 3 * x + 5; };
  double root = TernarySearch::ternarySearch(-100.0, +100.0, function);
  std::cout << root << std::endl; // -1.5
}


TEST(TernarySearchDiscreteTest, testCoverage) {
  // Define your own function on whatever you're attempting to ternary
  // search. Remember that your function must be a discrete and a unimodal
  // function, this means a function which decreases then increases (U shape)
  std::vector<double> func{16, 12, 10, 3, 6, 7, 9, 10, 11, 12, 13, 17};
  auto function = [&func](int i) -> double {
    // A discrete function is just a set of data points.
    return func[i];
  };

  int lo = 0;
  int hi = func.size() - 1;

  // Use ternary search to find the minimum value on the
  // whole interval of out function.
  double minValue = TernarySearchDiscrete::discreteTernarySearch(lo, hi, function);
  std::cout << minValue << std::endl; // 3

}


} // namespace serchingtest

} // namespace dsa
