/*
 * @file   MinimumWeightPerfectMatchingTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   15 July 2020
 * @version 0.1
 * @brief   MinimumWeightPerfectMatching Unit Test.
 */

#include <gtest\gtest.h>
#include <MinimumWeightPerfectMatching.h>

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

namespace minweightmatching {

class BruteForceMwpm {
private:
  int n_;
  std::vector<std::vector<double>> matrix_;
  double minWeightMatching_;

public:
  BruteForceMwpm(const std::vector<std::vector<double>>& matrix) {
    matrix_ = matrix;
    n_ = matrix.size();
    minWeightMatching_ = std::numeric_limits<double>::infinity();

//    for(int i = 0; i<n_; i++)
//      for(int j = 0; j<n_; j++)
//    	  std::cout << "(" << matrix[i][j] << "," << matrix_[i][j] << ") ";
//    std::cout << std::endl;
  }


  double getMinWeightCost() {
    solve();
    return minWeightMatching_;
  }


  double computeMatchingCost(const std::vector<int>& p) {
    double t = 0;
    for (int i = 0; i < n_ / 2; i++) {
      int ii = p[2 * i];
      int jj = p[2 * i + 1];
      t += matrix_[ii][jj];
    }
    return t;
  }


  void solve() {
	std::vector<int> permutation(n_);
    for (int i = 0; i < n_; i++) permutation[i] = i;

    // Try all matchings
    do {
//      for(int i = 0; i < n_; i++)
//        std::cout << "(" << permutation[i] << ") ";
//      std::cout << std::endl;
      double matchingCost = computeMatchingCost(permutation);
      if (matchingCost < minWeightMatching_) {
        minWeightMatching_ = matchingCost;
      }
    } while (nextPermutation(permutation));
  }


  // Generates the next ordered permutation in-place (skips repeated permutations).
  // Calling this when the array is already at the highest permutation returns false.
  // Recommended usage is to start with the smallest permutations and use a do while
  // loop to generate each successive permutations (see main for example).
  static bool nextPermutation(std::vector<int>& sequence) {
    int first = getFirst(sequence);
    if (first == -1) return false;
    int toSwap = sequence.size() - 1;
    while (sequence[first] >= sequence[toSwap]) --toSwap;
    swap(sequence, first++, toSwap);
    toSwap = sequence.size() - 1;
    while (first < toSwap) swap(sequence, first++, toSwap--);
    return true;
  }

private:
  static int getFirst(std::vector<int>& sequence) {
    for (int i = sequence.size() - 2; i >= 0; --i) if (sequence[i] < sequence[i + 1]) return i;
    return -1;
  }


  static void swap(std::vector<int>& sequence, int i, int j) {
    int tmp = sequence[i];
    sequence[i] = sequence[j];
    sequence[j] = tmp;
  }
};


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


void randomFillSymmetricMatrix(std::vector<std::vector<double>>& dist, int maxValue) {
  std::mt19937_64 rng;
  // initialize the random number generator with time-dependent seed
  uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
  rng.seed(ss);
  std::uniform_real_distribution<double> randDist(0, maxValue);


  for (unsigned i = 0; i < dist.size(); i++) {
    for (unsigned j = i + 1; j < dist.size(); j++) {
      double val = (int) (randDist(rng));
      dist[i][j] = dist[j][i] = val;
    }
  }
}

#if 1
static int LOOPS = 25;

TEST(MinimumWeightPerfectMatchingTest, testMatchingOutputsUniqueNodes) {
//	MinimumWeightPerfectMatching_test();
  for (int loop = 0; loop < LOOPS; loop++) {
    int n = std::max(1, genRandInt(1, 11) * 2); // n is either 2,4,6,8,10,12,14,16,18,20
    std::cout << "n:" << n << std::endl;
    std::vector<std::vector<double>> costMatrix(n, std::vector<double>(n));
    randomFillSymmetricMatrix(costMatrix, 100);

    MinimumWeightPerfectMatching mwpm = MinimumWeightPerfectMatching(costMatrix);
    std::vector<int> matching = mwpm.getMinWeightCostMatching();
    std::set<int> set;
    for (unsigned i = 0; i < matching.size(); i++) {
      set.insert(matching[i]);
    }

    EXPECT_EQ(set.size(), matching.size());
  }
}


TEST(MinimumWeightPerfectMatchingTest, testMatchingAndCostAreConsistent) {
  for (int loop = 0; loop < LOOPS; loop++) {
    int n = std::max(1, genRandInt(1, 11) * 2); // n is either 2,4,6,8,10,12,14,16,18,20
    std::vector<std::vector<double>> costMatrix(n, std::vector<double>(n));
    randomFillSymmetricMatrix(costMatrix, 100);

    MinimumWeightPerfectMatching mwpm = MinimumWeightPerfectMatching(costMatrix);
    std::vector<int> matching = mwpm.getMinWeightCostMatching();
    double totalMinCost = 0;
    for (unsigned i = 0; i < matching.size() / 2; i++) {
      int ii = matching[2 * i];
      int jj = matching[2 * i + 1];
      totalMinCost += costMatrix[ii][jj];
    }
    EXPECT_EQ(totalMinCost, mwpm.getMinWeightCost());
  }
}


TEST(MinimumWeightPerfectMatchingTest, testAgainstBruteForce_largeValues) {
  for (int loop = 0; loop < LOOPS; loop++) {
    int n = std::max(1, genRandInt(1, 6) * 2); // n is either 2,4,6,8, or 10
    std::vector<std::vector<double>> costMatrix(n, std::vector<double>(n));
    randomFillSymmetricMatrix(costMatrix, /*maxValue=*/ 10000);

    MinimumWeightPerfectMatching mwpm = MinimumWeightPerfectMatching(costMatrix);
    BruteForceMwpm bfMwpm = BruteForceMwpm(costMatrix);
    double dpSoln = mwpm.getMinWeightCost();
    double bfSoln = bfMwpm.getMinWeightCost();
    EXPECT_EQ(dpSoln, bfSoln);
  }
}


TEST(MinimumWeightPerfectMatchingTest, testAgainstBruteForce_smallValues) {
  for (int loop = 0; loop < LOOPS; loop++) {
    int n = std::max(1, genRandInt(1, 6) * 2); // n is either 2,4,6,8, or 10
    std::vector<std::vector<double>> costMatrix(n, std::vector<double>(n));
    randomFillSymmetricMatrix(costMatrix, /*maxValue=*/ 3);

    MinimumWeightPerfectMatching mwpm = MinimumWeightPerfectMatching(costMatrix);
    BruteForceMwpm bfMwpm = BruteForceMwpm(costMatrix);
    double dpSoln = mwpm.getMinWeightCost();
    double bfSoln = bfMwpm.getMinWeightCost();

    EXPECT_EQ(dpSoln, bfSoln);
  }
}
#endif
} // namespace minweightmatching
} // namespace dsa
