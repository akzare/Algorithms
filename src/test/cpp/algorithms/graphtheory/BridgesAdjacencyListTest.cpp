/*
 * @file   BridgesAdjacencyListTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   11 July 2020
 * @version 0.1
 * @brief   Bridges on an undirected graph unit test.
 */

#include <gtest\gtest.h>
#include <BridgesAdjacencyList.h>

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

std::set<std::pair<int, int>> getSortedBridges(const std::vector<int>& bridgeNodes) {
  std::set<std::pair<int, int>> bridges;
  for (unsigned i = 0; i < bridgeNodes.size(); i += 2) {
    int node1 = bridgeNodes[i];
    int node2 = bridgeNodes[i + 1];
    std::pair<int, int> pair;
    if (node1 < node2) {
      pair = std::make_pair(node1, node2);
    } else {
      pair = std::make_pair(node2, node1);
    }
    bridges.insert(pair);
  }
  return std::move(bridges);
}


// Every edge should be a bridge if the input a tree
TEST(BridgesAdjacencyListTest, testTreeCase) {
  Graph graph(12);
  graph.addUndirectedEdge(1, 0);
  graph.addUndirectedEdge(0, 2);
  graph.addUndirectedEdge(2, 5);
  graph.addUndirectedEdge(5, 6);
  graph.addUndirectedEdge(5, 11);
  graph.addUndirectedEdge(5, 4);
  graph.addUndirectedEdge(4, 10);
  graph.addUndirectedEdge(4, 3);
  graph.addUndirectedEdge(3, 7);
  graph.addUndirectedEdge(7, 8);
  graph.addUndirectedEdge(7, 9);

  std::unique_ptr<BridgesAdjacencyList> solver = std::make_unique<BridgesAdjacencyList>(&graph);
  std::set<std::pair<int, int>> sortedBridges = getSortedBridges(solver->findBridges());

  const std::set<std::pair<int, int>> expected{
      std::make_pair(0, 1),
      std::make_pair(0, 2),
      std::make_pair(2, 5),
      std::make_pair(5, 6),
      std::make_pair(5, 11),
      std::make_pair(4, 5),
      std::make_pair(4, 10),
      std::make_pair(3, 4),
      std::make_pair(3, 7),
      std::make_pair(7, 8),
      std::make_pair(7, 9)};

  EXPECT_EQ(sortedBridges, expected);

}


// Every edge should be a bridge if the input a tree
TEST(BridgesAdjacencyListTest, graphWithCyclesTest) {
  Graph graph(12);
  graph.addUndirectedEdge(1, 0);
  graph.addUndirectedEdge(0, 2);
  graph.addUndirectedEdge(3, 1);
  graph.addUndirectedEdge(2, 5);
  graph.addUndirectedEdge(5, 6);
  graph.addUndirectedEdge(5, 11);
  graph.addUndirectedEdge(5, 4);
  graph.addUndirectedEdge(4, 10);
  graph.addUndirectedEdge(4, 3);
  graph.addUndirectedEdge(3, 7);
  graph.addUndirectedEdge(7, 8);
  graph.addUndirectedEdge(7, 9);
  graph.addUndirectedEdge(11, 6);

  std::unique_ptr<BridgesAdjacencyList> solver = std::make_unique<BridgesAdjacencyList>(&graph);
  std::set<std::pair<int, int>> sortedBridges = getSortedBridges(solver->findBridges());

  const std::set<std::pair<int, int>> expected{
      std::make_pair(3, 7), std::make_pair(7, 8), std::make_pair(7, 9), std::make_pair(4, 10)};

  EXPECT_EQ(sortedBridges, expected);
}


TEST(BridgesAdjacencyListTest, testGraphInSlides) {
  Graph graph(9);
  graph.addUndirectedEdge(0, 1);
  graph.addUndirectedEdge(1, 2);
  graph.addUndirectedEdge(2, 3);
  graph.addUndirectedEdge(2, 5);
  graph.addUndirectedEdge(2, 0);
  graph.addUndirectedEdge(3, 4);
  graph.addUndirectedEdge(5, 6);
  graph.addUndirectedEdge(6, 7);
  graph.addUndirectedEdge(7, 8);
  graph.addUndirectedEdge(8, 5);

  std::unique_ptr<BridgesAdjacencyList> solver = std::make_unique<BridgesAdjacencyList>(&graph);
  std::set<std::pair<int, int>> sortedBridges = getSortedBridges(solver->findBridges());

  const std::set<std::pair<int, int>> expected{
      std::make_pair(2, 3), std::make_pair(3, 4), std::make_pair(2, 5)};

  EXPECT_EQ(sortedBridges, expected);
}


TEST(BridgesAdjacencyListTest, testDisconnectedGraph) {
  Graph graph(11);
  graph.addUndirectedEdge(0, 1);
  graph.addUndirectedEdge(2, 1);
  graph.addUndirectedEdge(3, 4);
  graph.addUndirectedEdge(5, 7);
  graph.addUndirectedEdge(5, 6);
  graph.addUndirectedEdge(6, 7);
  graph.addUndirectedEdge(8, 7);
  graph.addUndirectedEdge(8, 9);
  graph.addUndirectedEdge(8, 10);

  std::unique_ptr<BridgesAdjacencyList> solver = std::make_unique<BridgesAdjacencyList>(&graph);
  std::set<std::pair<int, int>> sortedBridges = getSortedBridges(solver->findBridges());

  const std::set<std::pair<int, int>> expected{
      std::make_pair(0, 1),
      std::make_pair(1, 2),
      std::make_pair(3, 4),
      std::make_pair(7, 8),
      std::make_pair(8, 9),
      std::make_pair(8, 10)};

  EXPECT_EQ(sortedBridges, expected);
}

} // namespace dsa
