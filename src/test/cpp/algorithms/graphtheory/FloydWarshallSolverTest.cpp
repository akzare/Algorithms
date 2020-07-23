/*
 * @file   BreadthFirstSearchAdjacencyListIterative.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   07 July 2020
 * @version 0.1
 * @brief   A BFS with an adjacency list unit test.
 */

#include <gtest\gtest.h>
#include <FloydWarshallSolver.h>
#include <BellmanFordAdjacencyMatrix.h>

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


class FloydWarshallSolverTest : public ::testing::Test {
protected:
  const double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
  const double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();

  int generateRandomInt(int begin, int end) {
    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);

    std::uniform_int_distribution<int> dist(begin, end);
    int r = dist(rng);
    return r==end ? r-1:r;
  }


  double generateRandomDouble(double begin, double end) {
    std::mt19937_64 rng;
    // initialize the random number generator with time-dependent seed
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed>>32)};
    rng.seed(ss);

    std::uniform_real_distribution<double> dist(begin, end);
    return dist(rng);
  }

  void addRandomEdges(std::vector<std::vector<double>>& matrix, int count, bool allowNegativeEdges) {
    int n = matrix[0].size();
    while (count-- > 0) {
      int i = generateRandomInt(0, n);
      int j = generateRandomInt(0, n);
      while (i == j) j = generateRandomInt(0, n);
//      std::cout << "n:" << n << " i:" << i << " j:" << j << std::endl;
      if (i == j) continue;
      int v = generateRandomInt(0, 100);
      // Allow negative edges but only very rarely since even one
      // negative edge can start an avalanche of negative cycles.
      if (allowNegativeEdges) v = (generateRandomDouble(0.0, 1.0) > 0.005) ? v : -v;
      matrix[i][j] = v;
//      std::cout << "v:" << matrix[i][j] << std::endl;
    }
  }

  void createMatrix(int n, std::vector<std::vector<double>> &m) {
    m = std::vector<std::vector<double>>(n, std::vector<double> (n, POSITIVE_INFINITY));
    for (int i = 0; i < n; i++) {
      m[i][i] = 0;
    }
  }


  std::vector<std::vector<double>> matrix1, matrix2, matrix3;

  FloydWarshallSolverTest() {
  }

  virtual ~FloydWarshallSolverTest() {
  }

  virtual void SetUp() {
    matrix1 = std::vector<std::vector<double>>{{0, POSITIVE_INFINITY, POSITIVE_INFINITY, POSITIVE_INFINITY, POSITIVE_INFINITY},
                                               {1, 0, 7, POSITIVE_INFINITY, POSITIVE_INFINITY},
                                               {POSITIVE_INFINITY, 3, 0, POSITIVE_INFINITY, POSITIVE_INFINITY},
                                               {13, POSITIVE_INFINITY, 4, 0, POSITIVE_INFINITY},
                                               {POSITIVE_INFINITY, POSITIVE_INFINITY, 3, 0, 0}};

    matrix2 = std::vector<std::vector<double>>{{0, 3, 1, 8, POSITIVE_INFINITY},
                                               {2, 0, 9, 4, POSITIVE_INFINITY},
                                               {POSITIVE_INFINITY, POSITIVE_INFINITY, 0, POSITIVE_INFINITY, -2},
                                               {POSITIVE_INFINITY, POSITIVE_INFINITY, 1, 0, POSITIVE_INFINITY},
                                               {POSITIVE_INFINITY, POSITIVE_INFINITY, POSITIVE_INFINITY, 0, 0}};

    matrix3 = std::vector<std::vector<double>>{{0, 6, POSITIVE_INFINITY, 25, 3},
                                               {1, 0, 6, 1, 3},
                                               {POSITIVE_INFINITY, 1, 0, 2, 3},
                                               {4, 4, 4, 0, POSITIVE_INFINITY},
                                               {4, 3, 5, POSITIVE_INFINITY, 0}};
  }



  virtual void TearDown() {
  }

};

#if 1
TEST_F(FloydWarshallSolverTest, testDirectedGraph) {
  std::unique_ptr<FloydWarshallSolver> solver = std::make_unique<FloydWarshallSolver>(matrix1);
  std::vector<std::vector<double>> soln = solver->getApspMatrix();

  EXPECT_EQ(soln[0][0], 0.0);
  EXPECT_EQ(soln[1][0], 1.0);
  EXPECT_EQ(soln[1][1], 0.0);
  EXPECT_EQ(soln[1][2], 7.0);
  EXPECT_EQ(soln[2][0], 4.0);
  EXPECT_EQ(soln[2][1], 3.0);
  EXPECT_EQ(soln[2][2], 0.0);
  EXPECT_EQ(soln[3][0], 8.0);
  EXPECT_EQ(soln[3][1], 7.0);
  EXPECT_EQ(soln[3][2], 4.0);
  EXPECT_EQ(soln[3][3], 0.0);
  EXPECT_EQ(soln[4][0], 7.0);
  EXPECT_EQ(soln[4][1], 6.0);
  EXPECT_EQ(soln[4][2], 3.0);
  EXPECT_EQ(soln[4][3], 0.0);
  EXPECT_EQ(soln[4][4], 0.0);
}


TEST_F(FloydWarshallSolverTest, testNegativeCycleGraph) {
  std::unique_ptr<FloydWarshallSolver> solver = std::make_unique<FloydWarshallSolver>(matrix2);
  std::vector<std::vector<double>> soln = solver->getApspMatrix();

  EXPECT_EQ(soln[0][0], 0.0);
  EXPECT_EQ(soln[0][1], 3.0);
  EXPECT_EQ(soln[0][2], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[0][3], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[0][4], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[1][0], 2.0);
  EXPECT_EQ(soln[1][1], 0.0);
  EXPECT_EQ(soln[1][2], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[1][3], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[1][4], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[2][2], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[2][3], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[2][4], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[3][2], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[3][3], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[3][4], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[4][2], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[4][3], NEGATIVE_INFINITY);
  EXPECT_EQ(soln[4][4], NEGATIVE_INFINITY);
}


TEST_F(FloydWarshallSolverTest, testApspAgainstBellmanFord_nonNegativeEdgeWeights) {
//  BellmanFord_test();

  int TRAILS = 10;
  for (int n = 2; n <= 25; n++) {
    for (int trail = 1; trail <= TRAILS; trail++) {
      std::vector<std::vector<double>> m;
      createMatrix(n, m);
      int numRandomEdges = std::max(1, generateRandomInt(0, n));
      addRandomEdges(m, numRandomEdges, false);
      std::unique_ptr<FloydWarshallSolver> solver = std::make_unique<FloydWarshallSolver>(m);
      std::vector<std::vector<double>> fw = solver->getApspMatrix();

      for (int s = 0; s < n; s++) {
        std::unique_ptr<BellmanFordAdjacencyMatrix> bfSolver = std::make_unique<BellmanFordAdjacencyMatrix>(s, &m);
    	std::vector<double> bf = bfSolver->getShortestPaths();
    	EXPECT_EQ(bf, fw[s]);
    	bfSolver = nullptr;
      }
      solver = nullptr;
    }
  }
}


TEST_F(FloydWarshallSolverTest, testApspAgainstBellmanFord_withNegativeEdgeWeights) {
  int TRAILS = 10;
  for (int n = 2; n <= 25; n++) {
    for (int trail = 1; trail <= TRAILS; trail++) {

      std::vector<std::vector<double>> m;
      createMatrix(n, m);
      int numRandomEdges = std::max(1, generateRandomInt(0, n));
      addRandomEdges(m, numRandomEdges, true);
      std::unique_ptr<FloydWarshallSolver> solver = std::make_unique<FloydWarshallSolver>(m);
      std::vector<std::vector<double>> fw = solver->getApspMatrix();

      for (int s = 0; s < n; s++) {
        std::unique_ptr<BellmanFordAdjacencyMatrix> bfSolver = std::make_unique<BellmanFordAdjacencyMatrix>(s, &m);
      	std::vector<double> bf = bfSolver->getShortestPaths();
      	EXPECT_EQ(bf, fw[s]);
      	bfSolver = nullptr;
      }
      solver = nullptr;
    }
  }
}


// Tests for a mismatch in how both algorithms detect the existence of
// a negative cycle on the shortest path from s -> e.
TEST_F(FloydWarshallSolverTest, testPathReconstructionBellmanFord_nonNegativeEdgeWeights) {
  int TRAILS = 50;
  for (int n = 2; n <= 25; n++) {
    for (int trail = 1; trail <= TRAILS; trail++) {

      std::vector<std::vector<double>> m;
      createMatrix(n, m);
      int numRandomEdges = std::max(1, generateRandomInt(0, n));
      addRandomEdges(m, numRandomEdges, true);
      std::unique_ptr<FloydWarshallSolver> fwSolver = std::make_unique<FloydWarshallSolver>(m);
      fwSolver->solve();

      for (int s = 0; s < n; s++) {
        std::unique_ptr<BellmanFordAdjacencyMatrix> bfSolver = std::make_unique<BellmanFordAdjacencyMatrix>(s, &m);
        for (int e = 0; e < n; e++) {

          // Make sure that if 'fwp' returns null that 'bfp' also returns null or
          // that if 'fwp' is not null that 'bfp' is also not null.
          std::list<int> fwp;
          bool isNegCycle;
          std::tie(isNegCycle, fwp) = fwSolver->reconstructShortestPath(s, e);

          std::list<int> bfp;
          bfSolver->reconstructShortestPath(e, bfp);
          if ((fwp.size() == 0) ^ (bfp.size() == 0)) {
            std::cout << "Mismatch." << std::endl;
          }
        }
      }
    }
  }
}


TEST_F(FloydWarshallSolverTest, testSimpleNegativeCycleDetection) {
  int n = 3, s = 0, e = 2;
  std::vector<std::vector<double>> m;
  createMatrix(n, m);
  m[0][1] = 100;
  m[0][2] = 5;
  m[1][2] = 0;
  m[1][1] = -1; // negative self loop.
  std::unique_ptr<FloydWarshallSolver> fw = std::make_unique<FloydWarshallSolver>(m);
  std::list<int> fwPath;
  bool isNegCycle;
  std::tie(isNegCycle, fwPath) = fw->reconstructShortestPath(s, e);
  EXPECT_TRUE(isNegCycle);
}


TEST_F(FloydWarshallSolverTest, testNegativeCyclePropagation) {
  int n = 100, s = 0, e = n - 1;
  std::vector<std::vector<double>> m;
  createMatrix(n, m);
  for (int i = 1; i < n; i++) m[i - 1][i] = 10;
  m[1][0] = -11;
  std::unique_ptr<FloydWarshallSolver> fw = std::make_unique<FloydWarshallSolver>(m);
  std::list<int> fwPath;
  bool isNegCycle;
  std::tie(isNegCycle, fwPath) = fw->reconstructShortestPath(s, e);
  EXPECT_TRUE(isNegCycle);
}
#endif
} // namespace dsa
