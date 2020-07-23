/*
 * @file   TarjanSccSolverAdjacencyListTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   11 July 2020
 * @version 0.1
 * @brief   A Tarjan's Strongly Connected Components unit test.
 */

#include <gtest\gtest.h>
#include <TarjanSccSolverAdjacencyList.h>

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

TEST(TarjanSccSolverAdjacencyListTest, singletonCase) {
  int n = 1;
  Graph graph(n);

  std::unique_ptr<TarjanSccSolverAdjacencyList> solver = std::make_unique<TarjanSccSolverAdjacencyList>(&graph);
  std::set<std::set<int>> sccList = solver->getSccs();
  std::set<std::set<int>> expected{{0}};
  EXPECT_EQ(sccList, expected);
  EXPECT_EQ(solver->sccCount(), 1);
  solver = nullptr;
}


TEST(TarjanSccSolverAdjacencyListTest, testTwoDisjointComponents) {
//  TarjanScc_test();

  int n = 5;
  Graph graph(n);

  graph.addDirectedEdge(0, 1);
  graph.addDirectedEdge(1, 0);
  graph.addDirectedEdge(2, 3);
  graph.addDirectedEdge(3, 4);
  graph.addDirectedEdge(4, 2);

  std::unique_ptr<TarjanSccSolverAdjacencyList> solver = std::make_unique<TarjanSccSolverAdjacencyList>(&graph);
  std::set<std::set<int>> sccList = solver->getSccs();

//  std::cout << "Number of Strongly Connected Components: " << solver->sccCount() << std::endl;
//  TarjanSccSolverAdjacencyList::printSCCList(sccList);

  std::set<std::set<int>> expectedSccs{{0, 1}, {2, 3, 4}};
  EXPECT_EQ(solver->sccCount(), expectedSccs.size());
  EXPECT_EQ(sccList, expectedSccs);
  solver = nullptr;
}


TEST(TarjanSccSolverAdjacencyListTest, testButterflyCase) {
  int n = 5;
  Graph graph(n);

  graph.addDirectedEdge(0, 1);
  graph.addDirectedEdge(1, 2);
  graph.addDirectedEdge(2, 3);
  graph.addDirectedEdge(3, 1);
  graph.addDirectedEdge(1, 4);
  graph.addDirectedEdge(4, 0);

  std::unique_ptr<TarjanSccSolverAdjacencyList> solver = std::make_unique<TarjanSccSolverAdjacencyList>(&graph);
  std::set<std::set<int>> sccList = solver->getSccs();

  std::set<std::set<int>> expectedSccs{{0, 1, 2, 3, 4}};
  EXPECT_EQ(solver->sccCount(), expectedSccs.size());
  EXPECT_EQ(sccList, expectedSccs);
  solver = nullptr;
}


TEST(TarjanSccSolverAdjacencyListTest, testFirstGraphInSlides) {
  int n = 9;
  Graph graph(n);

  graph.addDirectedEdge(0, 1);
  graph.addDirectedEdge(1, 0);
  graph.addDirectedEdge(0, 8);
  graph.addDirectedEdge(8, 0);
  graph.addDirectedEdge(8, 7);
  graph.addDirectedEdge(7, 6);
  graph.addDirectedEdge(6, 7);
  graph.addDirectedEdge(1, 7);
  graph.addDirectedEdge(2, 1);
  graph.addDirectedEdge(2, 6);
  graph.addDirectedEdge(5, 6);
  graph.addDirectedEdge(2, 5);
  graph.addDirectedEdge(5, 3);
  graph.addDirectedEdge(3, 2);
  graph.addDirectedEdge(4, 3);
  graph.addDirectedEdge(4, 5);

  std::unique_ptr<TarjanSccSolverAdjacencyList> solver = std::make_unique<TarjanSccSolverAdjacencyList>(&graph);
  std::set<std::set<int>> sccList = solver->getSccs();

  std::cout << "Number of Strongly Connected Components: " << solver->sccCount() << std::endl;
  TarjanSccSolverAdjacencyList::printSCCList(sccList);

  std::set<std::set<int>> expectedSccs{{0, 1, 8}, {7, 6}, {2, 3, 5}, {4}};
  EXPECT_EQ(solver->sccCount(), expectedSccs.size());
  EXPECT_EQ(sccList, expectedSccs);
  solver = nullptr;
}


TEST(TarjanSccSolverAdjacencyListTest, testLastGraphInSlides) {
  int n = 8;
  Graph graph(n);

  graph.addDirectedEdge(6, 0);
  graph.addDirectedEdge(6, 2);
  graph.addDirectedEdge(3, 4);
  graph.addDirectedEdge(6, 4);
  graph.addDirectedEdge(2, 0);
  graph.addDirectedEdge(0, 1);
  graph.addDirectedEdge(4, 5);
  graph.addDirectedEdge(5, 6);
  graph.addDirectedEdge(3, 7);
  graph.addDirectedEdge(7, 5);
  graph.addDirectedEdge(1, 2);
  graph.addDirectedEdge(7, 3);
  graph.addDirectedEdge(5, 0);

  std::unique_ptr<TarjanSccSolverAdjacencyList> solver = std::make_unique<TarjanSccSolverAdjacencyList>(&graph);
  std::set<std::set<int>> sccList = solver->getSccs();
  std::set<std::set<int>> expectedSccs{{0, 2, 1}, {3, 7}, {6, 5, 4}};
  EXPECT_EQ(solver->sccCount(), expectedSccs.size());
  EXPECT_EQ(sccList, expectedSccs);
  solver = nullptr;
}

} // namespace dsa
