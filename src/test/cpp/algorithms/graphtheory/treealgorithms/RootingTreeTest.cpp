/*
 * @file   MathTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   15 July 2020
 * @version 0.1
 * @brief   Math Unit Test.
 */

#include <gtest\gtest.h>
#include <RootingTree.h>

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


TEST(RootingTreeTest, testSimpleRooting1) {
  Graph graph(9);
  graph.addUndirectedEdge(0, 1);
  graph.addUndirectedEdge(2, 1);
  graph.addUndirectedEdge(2, 3);
  graph.addUndirectedEdge(3, 4);
  graph.addUndirectedEdge(5, 3);
  graph.addUndirectedEdge(2, 6);
  graph.addUndirectedEdge(6, 7);
  graph.addUndirectedEdge(6, 8);
  // Graph 1 rooted at 6 should look like:
  //           6
  //      2    7     8
  //    1   3
  //  0    4 5

  std::unique_ptr<RootingTree> node6 = std::make_unique<RootingTree>(&graph, 6);

  // Layer 0: [6]
  EXPECT_EQ((*node6)().id(), 6);
  EXPECT_EQ((*node6)().parent(), nullptr);


  std::unordered_set<RootingTree::TreeNode*> children_root = node6->children();
  std::set<int> expectedIds_node6{2,7,8};
  std::set<int> expectedIds_node2{1,3};
  std::set<int> expectedIds_node3{4,5};
  std::set<int> expectedIds_node1{0};
  std::set<int> asIsIds_node6;
  std::set<int> asIsIds_node2;
  std::set<int> asIsIds_node3;
  std::set<int> asIsIds_node1;
  for (auto c : children_root) { // Layer 1 node 6(root): [2, 7, 8]
    asIsIds_node6.insert((*c).id());
    if ((*c).id() == 2) { // Layer 2 node 2: [1, 3]
      std::unordered_set<RootingTree::TreeNode*> children_node2 = (*c).children();
      for (auto c2 : children_node2) {
        asIsIds_node2.insert((*c2).id());
        if ((*c2).id() == 3) { // Layer 3 node 3: [4, 5]
          std::unordered_set<RootingTree::TreeNode*> children_node3 = (*c2).children();
          for (auto c3 : children_node3) {
            asIsIds_node3.insert((*c3).id());
          }
        }
        if ((*c2).id() == 1) { // Layer 3 node 1: [0]
          std::unordered_set<RootingTree::TreeNode*> children_node1 = (*c2).children();
          for (auto c1 : children_node1) {
            asIsIds_node1.insert((*c1).id());
          }
        }
      }
    }
  }

  EXPECT_EQ(asIsIds_node6, expectedIds_node6);
  EXPECT_EQ(asIsIds_node2, expectedIds_node2);
  EXPECT_EQ(asIsIds_node3, expectedIds_node3);
  EXPECT_EQ(asIsIds_node1, expectedIds_node1);

  // TODO(williamfiset): also verify the parent pointers are pointing at the correct nodes.
}


TEST(RootingTreeTest, testSimpleRootingPrint) {
  Graph graph(9);

  graph.addUndirectedEdge(0, 1);
  graph.addUndirectedEdge(2, 1);
  graph.addUndirectedEdge(2, 3);
  graph.addUndirectedEdge(3, 4);
  graph.addUndirectedEdge(5, 3);
  graph.addUndirectedEdge(2, 6);
  graph.addUndirectedEdge(6, 7);
  graph.addUndirectedEdge(6, 8);

  // Rooted at 6 the tree should look like:
  //           6
  //      2    7     8
  //    1   3
  //  0    4 5

  RootingTree *root = new RootingTree(&graph, 6);

  // Layer 0: [6]
  std::cout << "Layer 0: [6]: ";
  std::cout << (*root) << std::endl;


#define PRINT_CHILDREN(r) \
  do { \
	std::cout << "["; \
	for (auto c : r) std::cout << (*c) << ","; \
	std::cout << "]"; \
  } while(0)


  // Layer 1: [2, 7, 8]
  std::unordered_set<RootingTree::TreeNode*> children_root = root->children();
  std::cout << "Layer 1: [2, 7, 8]: ";
  PRINT_CHILDREN(children_root);
  std::cout << std::endl;


  // Layer 2: [1, 3]
  int expectedId = 2;
  auto idComparer = [&expectedId](auto c2) -> bool { return ((*c2).id() == expectedId); };
  auto itr = std::find_if(children_root.begin(), children_root.end(), idComparer);
  std::unordered_set<RootingTree::TreeNode*> children_layer2 = (*itr)->children();
  std::cout << "Layer 2: [1, 3]: ";
  PRINT_CHILDREN(children_layer2);
  std::cout << std::endl;


  // Layer 3: [0], [4, 5]
  expectedId = 3;
  itr = std::find_if(children_layer2.begin(), children_layer2.end(), idComparer);
  std::unordered_set<RootingTree::TreeNode*> children_layer3 = (*itr)->children();
  std::cout << "Layer 3: [4, 5]: ";
  PRINT_CHILDREN(children_layer3);
  std::cout << std::endl;

  delete root;
}

} // namespace dsa
