/*
 * @file   TarjanSccSolverAdjacencyListTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   11 July 2020
 * @version 0.1
 * @brief   Traveling salesman problem unit test.
 */

#include <gtest\gtest.h>
#include <TspBruteForce.h>
#include <TspDynamicProgrammingIterative.h>

#include <chrono>
#include <random>
#include <list>
#include <vector>
#include <queue>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>

namespace dsa {

static const double EPS = 1e-5;

double genRandomDouble(double begin, double end) {
  std::mt19937_64 rng;
  // initialize the random number generator with time-dependent seed
  uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
  rng.seed(ss);

  std::uniform_real_distribution<double> dist(begin, end);
  return dist(rng);
}

void randomFillDistMatrix(std::vector<std::vector<double>> &dist) {
  for (unsigned i = 0; i < dist.size(); i++) {
    for (unsigned j = 0; j < dist[i].size(); j++) {
      if (i == j) continue;

      // Add a random edge value (possibly negative)
      double val = genRandomDouble(0, 1000.0);
      if (genRandomDouble(0, 1.0) < 0.8) dist[i][j] = val;
      else dist[i][j] = -val;
    }
  }
}


double getTourCost(const std::vector<std::vector<double>> &dist, const std::list<int> &tour) {
  double total = 0;
  for (auto it = tour.cbegin(); it != tour.cend(); ++it) {
	if (std::next(it, 1) == tour.cend()) break;
    total += dist[*it][*std::next(it, 1)];
  }
  return total;
}

#if 1
TEST(TravelingSalesmanProblemTest, testTspIterativeInvalidStartNode) {
  try {
	std::vector<std::vector<double>> dist{{1, 2, 3},
                                          {4, 5, 6},
                                          {7, 8, 9}};
    std::unique_ptr<TspDynamicProgrammingIterative> solver = std::make_unique<TspDynamicProgrammingIterative>(321, dist);
  }
  catch(std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("Invalid start node."));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Invalid start node.";
  }

}


TEST(TravelingSalesmanProblemTest, testTspIterativeNonSquareMatrix) {
  try {
	std::vector<std::vector<double>> dist{{1, 2, 3},
                                          {4, 5, 6}};
    std::unique_ptr<TspDynamicProgrammingIterative> solver = std::make_unique<TspDynamicProgrammingIterative>(321, dist);
  }
  catch(std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("Matrix must be square (n x n)"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Matrix must be square (n x n)";
  }
}


TEST(TravelingSalesmanProblemTest, testTspIterativeSmallGraph) {
  try {
	std::vector<std::vector<double>> dist{{0, 1},
                                          {1, 0}};
    std::unique_ptr<TspDynamicProgrammingIterative> solver = std::make_unique<TspDynamicProgrammingIterative>(321, dist);
  }
  catch(std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("N <= 2 not yet supported."));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error N <= 2 not yet supported.";
  }
}


TEST(TravelingSalesmanProblemTest, testTsp_small1) {
  int n = 5;
  std::vector<std::vector<double>> dist(n, std::vector<double> (n, 100));

  // Assume matrix is symmetric for simplicity.
  dist[1][3] = dist[3][1] = 1;
  dist[3][0] = dist[0][3] = 2;
  dist[0][2] = dist[2][0] = 3;
  dist[2][4] = dist[4][2] = 4;
  dist[4][1] = dist[1][4] = 5;

  double expected = 1 + 2 + 3 + 4 + 5;
//  double tspRecursiveTourCost = new TspDynamicProgrammingRecursive(dist).getTourCost();
  std::unique_ptr<TspDynamicProgrammingIterative> solver = std::make_unique<TspDynamicProgrammingIterative>(dist);
  double tspIterativeTourCost = solver->getTourCost();

//  EXPECT_DOUBLE_EQ(tspRecursiveTourCost, expected);
  EXPECT_DOUBLE_EQ(tspIterativeTourCost, expected);
}


TEST(TravelingSalesmanProblemTest, testDpVsBf) {
  for (int n = 3; n <= 9; n++) {
    for (int i = 0; i < 10; i++) {

      std::vector<std::vector<double>> dist(n, std::vector<double> (n, 100));
      randomFillDistMatrix(dist);

//      TspDynamicProgrammingRecursive dpRecursiveSolver = new TspDynamicProgrammingRecursive(dist);
      std::unique_ptr<TspDynamicProgrammingIterative> dpIterativeSolver = std::make_unique<TspDynamicProgrammingIterative>(dist);

//      double dp1 = dpRecursiveSolver.getTourCost();
      double dp2 = dpIterativeSolver->getTourCost();
      double bf = TspBruteForce::computeTourCost(TspBruteForce::tsp(dist), dist);

//      EXPECT_DOUBLE_EQ(dp1, bf);
      EXPECT_NEAR(dp2, bf, EPS);
    }
  }
}


TEST(TravelingSalesmanProblemTest, testGeneratedTour) {
  for (int n = 3; n <= 9; n++) {
    for (int i = 0; i < 10; i++) {

      std::vector<std::vector<double>> dist(n, std::vector<double> (n, 100));
      randomFillDistMatrix(dist);

//      TspDynamicProgrammingRecursive dpRecursiveSolver = new TspDynamicProgrammingRecursive(dist);
      std::unique_ptr<TspDynamicProgrammingIterative> dpIterativeSolver = std::make_unique<TspDynamicProgrammingIterative>(dist);
      std::vector<int> bfPath = TspBruteForce::tsp(dist);

//      double dp1 = dpRecursiveSolver.getTourCost();
      double dp2 = dpIterativeSolver->getTourCost();
      double bf = TspBruteForce::computeTourCost(bfPath, dist);

//      EXPECT_DOUBLE_EQ(dp1, bf);
      EXPECT_NEAR(dp2, bf, EPS);
//      EXPECT_DOUBLE_EQ(dp2, bf);

//      EXPECT_DOUBLE_EQ(getTourCost(dist, dpRecursiveSolver->getTour()), bf);
      EXPECT_NEAR(getTourCost(dist, dpIterativeSolver->getTour()), bf, EPS);
    }
  }
}


TEST(TravelingSalesmanProblemTest, testDifferentStartingNodes) {
  for (int n = 3; n <= 9; n++) {

    std::vector<std::vector<double>> dist(n, std::vector<double> (n, 100));
    randomFillDistMatrix(dist);
    std::vector<int> bfPath = TspBruteForce::tsp(dist);
    double bf = TspBruteForce::computeTourCost(bfPath, dist);

    for (int startNode = 0; startNode < n; startNode++) {
//      TspDynamicProgrammingRecursive dpRecursiveSolver =
//          new TspDynamicProgrammingRecursive(startNode, dist);
      std::unique_ptr<TspDynamicProgrammingIterative> dpIterativeSolver = std::make_unique<TspDynamicProgrammingIterative>(startNode, dist);

//      double dp1 = dpRecursiveSolver.getTourCost();
      double dp2 = dpIterativeSolver->getTourCost();

//      EXPECT_DOUBLE_EQ(dp1, bf);
      EXPECT_NEAR(dp2, bf, EPS);

//      EXPECT_DOUBLE_EQ(getTourCost(dist, dpRecursiveSolver->getTour()), bf);
      EXPECT_NEAR(getTourCost(dist, dpIterativeSolver->getTour()), bf, EPS);
    }
  }
}


// Try slightly larger matrices to make sure they run is a reasonable amount of time.
//TEST(TravelingSalesmanProblemTest, testTspRecursivePerformance) {
//  for (int n = 3; n <= 16; n++) {
//	std::vector<std::vector<double>> dist(n, std::vector<double> (n, 100));
//    randomFillDistMatrix(dist);
//    TspDynamicProgrammingRecursive solver = new TspDynamicProgrammingRecursive(dist);
//    solver->getTourCost();
//  }
//}


// Try slightly larger matrices to make sure they run is a reasonable amount of time.
TEST(TravelingSalesmanProblemTest, testTspIterativePerformance) {
  for (int n = 3; n <= 16; n++) {
    std::vector<std::vector<double>> dist(n, std::vector<double> (n, 100));
    randomFillDistMatrix(dist);
    std::unique_ptr<TspDynamicProgrammingIterative> solver = std::make_unique<TspDynamicProgrammingIterative>(dist);
    solver->getTourCost();
  }
}

/*
ToDo: The following test cases need to be implemented!

//  @Test(expected = IllegalArgumentException.class)
TEST(TravelingSalesmanProblemTest, testTspRecursiveInvalidStartNode) {
  double[][] dist = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
  };
  new TspDynamicProgrammingRecursive(321, dist);
}


//  @Test(expected = IllegalStateException.class)
TEST(TravelingSalesmanProblemTest, testTspRecursiveNonSquareMatrix) {
  double[][] dist = {
    {1, 2, 3},
    {4, 5, 6}
  };
  new TspDynamicProgrammingRecursive(dist);
}


//  @Test(expected = IllegalStateException.class)
TEST(TravelingSalesmanProblemTest, testTspRecursiveSmallGraph) {
  double[][] dist = {
    {0, 1},
    {1, 0}
  };
  new TspDynamicProgrammingRecursive(dist);
}

*/
#endif
} // namespace dsa
