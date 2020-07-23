/*
 * @file   BreadthFirstSearchAdjacencyListIterative.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   07 July 2020
 * @version 0.1
 * @brief   A BFS with an adjacency list unit test.
 */

#include <gtest\gtest.h>
#include <BreadthFirstSearchAdjacencyListIterative.h>
#include <DepthFirstSearchAdjacencyListIterative.h>
#include <TopologicalSortAdjacencyList.h>
#include <DijkstrasShortestPathAdjacencyList.h>
#include <DijkstrasShortestPathAdjacencyListWithDHeap.h>

#include <chrono>
#include <random>
#include <list>
#include <queue>
#include <iterator>
#include <vector>
#include <algorithm>
#include <limits>

namespace dsa {

std::random_device rd;

int generateRandomInt(int begin, int end) {
	std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(begin, end);
  int res = (int)dist(mt);
  return res < end ? res:end-1;
}


std::vector<std::vector<double>> generateRandomGraph(Graph &graph1, int n) {
  std::vector<std::vector<bool>> edgeMatrix(n, std::vector<bool> (n, false));
  std::vector<std::vector<double>> graph2(n, std::vector<double> (n, std::numeric_limits<double>::max()));
#if 0
  std::cout << "b edgeMatrix[";
  for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) std::cout << edgeMatrix[i][j] << ","; std::cout << std::endl; }
  std::cout << "]" << std::endl;

  std::cout << "b graph2[";
  for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) std::cout << graph2[i][j] << ","; std::cout << std::endl; }
  std::cout << "]" << std::endl;
#endif
  int numEdges = std::max(1, (int) (generateRandomInt(0, n) * n));
  int u_old = 0;
  int v_old = 0;
  for (int i = 0; i < numEdges; i++) {
	int u = generateRandomInt(0, n);
    while (u == u_old) u = generateRandomInt(0, n);
    int v = generateRandomInt(0, n);
    while (v == v_old) v = generateRandomInt(0, n);
//    std::cout << "u:" << u << " v:" << v << std::endl;
    if (!edgeMatrix[u][v]) {
      graph1.addUnweightedUndirectedEdge(u, v);
      graph2[u][v] = 1;
      graph2[v][u] = 1;
      edgeMatrix[u][v] = true;
      edgeMatrix[v][u] = true;
    }
    u_old = u;
    v_old = v;
  }
#if 0
  std::cout << "a edgeMatrix[";
  for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) std::cout << edgeMatrix[i][j] << ","; std::cout << std::endl; }
  std::cout << "]" << std::endl;

  std::cout << "a graph2[";
  for (int i = 0; i < n; i++) { for (int j = 0; j < n; j++) std::cout << graph2[i][j] << ","; std::cout << std::endl; }
  std::cout << "]" << std::endl;
#endif
  return graph2;
}


#if 1
TEST(BreadthFirstSearchAdjacencyListIterativeTest, testSingletonGraph) {

  try {
	Graph graph(1);
	BreadthFirstSearchAdjacencyListIterative solver(&graph);
	std::list<int> path;
	solver.reconstructPath(10, 5, path);
  }
  catch(std::invalid_argument const &err) {
    EXPECT_EQ(err.what(), std::string("Invalid end node index"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Invalid end node index";
  }
}


TEST(BreadthFirstSearchAdjacencyListIterativeTest, testTwoNodeGraph) {
  Graph graph(2);
  graph.addUnweightedUndirectedEdge(0, 1);
  BreadthFirstSearchAdjacencyListIterative solver(&graph);

  std::list<int> expected;
  expected.push_back(0);
  expected.push_back(1);

  std::list<int> path;
  solver.reconstructPath(0, 1, path);
  EXPECT_EQ(path, expected);
}


TEST(BreadthFirstSearchAdjacencyListIterativeTest, testThreeNodeGraph) {
  Graph graph(3);
  graph.addUnweightedUndirectedEdge(0, 1);
  graph.addUnweightedUndirectedEdge(2, 1);
  BreadthFirstSearchAdjacencyListIterative solver(&graph);

//  std::cout << graph << std::endl;
//  std::cout << solver() << std::endl;

  std::list<int> expected;
  expected.push_back(0);
  expected.push_back(1);
  expected.push_back(2);

  std::list<int> path;
  solver.reconstructPath(0, 2, path);
  EXPECT_EQ(path, expected);
}


TEST(BreadthFirstSearchAdjacencyListIterativeTest, testShortestPathAgainstBellmanFord) {
  int loops = 20;
  for (int i = 0, n = 2; i < loops; i++, n++)
  {
    Graph graph(n);

//    std::cout << graph << std::endl;
    std::vector<std::vector<double>> graph2 = generateRandomGraph(graph, n);
//    std::cout << graph << std::endl;

    BreadthFirstSearchAdjacencyListIterative solver(&graph);
//    BellmanFordAdjacencyMatrix bfSolver(s, graph2);

    int s_old = 0;
    int e_old = 0;

    for (int j = 0 ; j < n; j++) {
      int s = generateRandomInt(0, n);
      while (s == s_old) s = generateRandomInt(0, n);
      int e = generateRandomInt(0, n);
      while (e == e_old) e = generateRandomInt(0, n);

      std::list<int> p1;
      solver.reconstructPath(s, e, p1);
//    std::list<int> p2 = bfSolver.reconstructShortestPath(e);
//    EXPECT_EQ(p1.size(), p2.size());
      std::cout << Graph::formatPath(s, e, p1) << std::endl;
      s_old = s;
      e_old = e;
    }

  }
}


TEST(DepthFirstSearchAdjacencyListIterativeTest, testFiveNodeGraph) {
  Graph graph(5);

  graph.addDirectedEdge(0, 1, 4.0);
  graph.addDirectedEdge(0, 2, 5.0);
  graph.addDirectedEdge(1, 2, -2.0);
  graph.addDirectedEdge(1, 3, 6.0);
  graph.addDirectedEdge(2, 3, 1.0);
  graph.addDirectedEdge(2, 2, 10.0); // Self loop

  DepthFirstSearchAdjacencyListIterative solver(&graph);

  int nodeCount = solver.dfs(0);
  std::cout << "DFS node count starting at node 0: " <<  nodeCount << std::endl;
  EXPECT_EQ(nodeCount, 4);

  nodeCount = solver.dfs(4);
  std::cout << "DFS node count starting at node 4:" <<  nodeCount << std::endl;
  EXPECT_EQ(nodeCount, 1);

}


TEST(TopologicalSortAdjacencyListTest, testSevenNodeGraph) {
  Graph graph(7);

  graph.addDirectedEdge(0, 1, 3.0);
  graph.addDirectedEdge(0, 2, 2.0);
  graph.addDirectedEdge(0, 5, 3.0);
  graph.addDirectedEdge(1, 3, 1.0);
  graph.addDirectedEdge(1, 2, 6.0);
  graph.addDirectedEdge(2, 3, 1.0);
  graph.addDirectedEdge(2, 4, 10.0);
  graph.addDirectedEdge(3, 4, 5.0);
  graph.addDirectedEdge(5, 4, 7.0);

  TopologicalSortAdjacencyList solver(&graph);

  std::vector<int> ordering = solver.topologicalSort();

  // Prints: [6, 0, 5, 1, 2, 3, 4]
  {
  std::stringstream ss;
  for (auto node: ordering) {
    ss << "-> ";
    ss << node;
  }
  std::string s = ss.str();
  std::cout << "Ordering :" << s << std::endl;
  }

  // Finds all the shortest paths starting at node 0
  std::vector<int> dists = solver.dagShortestPath(0);

  // Find the shortest path from 0 to 4 which is 8
  std::cout << "Find the shortest path from 0 to 4: " << dists[4] << std::endl;
  EXPECT_EQ(dists[4], 8);

  // Find the shortest path from 0 to 6 which
  // is null since 6 is not reachable!
  std::cout << "Find the shortest path from 0 to 6: " << dists[6] << std::endl;
  EXPECT_EQ(dists[6], -1);
}


TEST(DijkstrasShortestPathAdjacencyListTest, testEightNodeGraph) {
  Graph graph(8);

  graph.addDirectedEdge(6, 0, 1.1);
  graph.addDirectedEdge(6, 2, 0.2);
  graph.addDirectedEdge(3, 4, 3.6);
  graph.addDirectedEdge(6, 4, 0.4);
  graph.addDirectedEdge(2, 0, 0.7);
  graph.addDirectedEdge(0, 1, 3.4);
  graph.addDirectedEdge(4, 5, 6.9);
  graph.addDirectedEdge(5, 6, 0.9);
  graph.addDirectedEdge(3, 7, 8.2);
  graph.addDirectedEdge(7, 5, 0.3);
  graph.addDirectedEdge(1, 2, 4.6);
  graph.addDirectedEdge(7, 3, 6.4);
  graph.addDirectedEdge(5, 0, 10.1);

  std::unique_ptr<DijkstrasShortestPathAdjacencyList> solver = std::make_unique<DijkstrasShortestPathAdjacencyList>(&graph);

  int start = 3, end = 0;

  std::list<int> path = solver->reconstructPath(start, end);

  std::cout << "Dijkstras Shortest Path from " << start << " to " << end << ": [";
  if (!path.empty()) {
    for (auto edge: path){
      std::cout << edge << ",";
    }
  }
  std::cout << "]" << std::endl;

  solver = nullptr;
}



TEST(DijkstrasShortestPathAdjacencyListDHeapTest, testEightNodeGraph) {
  Graph graph(8);

  graph.addDirectedEdge(6, 0, 1.1);
  graph.addDirectedEdge(6, 2, 0.2);
  graph.addDirectedEdge(3, 4, 3.6);
  graph.addDirectedEdge(6, 4, 0.4);
  graph.addDirectedEdge(2, 0, 0.7);
  graph.addDirectedEdge(0, 1, 3.4);
  graph.addDirectedEdge(4, 5, 6.9);
  graph.addDirectedEdge(5, 6, 0.9);
  graph.addDirectedEdge(3, 7, 8.2);
  graph.addDirectedEdge(7, 5, 0.3);
  graph.addDirectedEdge(1, 2, 4.6);
  graph.addDirectedEdge(7, 3, 6.4);
  graph.addDirectedEdge(5, 0, 10.1);

  std::unique_ptr<DijkstrasShortestPathAdjacencyListWithDHeap> solver = std::make_unique<DijkstrasShortestPathAdjacencyListWithDHeap>(&graph);

  int start = 3, end = 0;

  std::list<int> path = solver->reconstructPath(start, end);

  std::cout << "Dijkstras Shortest Path with DHeap from " << start << " to " << end << ": [";
  if (!path.empty()) {
    for (auto edge: path){
      std::cout << edge << ",";
    }
  }
  std::cout << "]" << std::endl;

  solver = nullptr;
}
#endif
} // namespace dsa
