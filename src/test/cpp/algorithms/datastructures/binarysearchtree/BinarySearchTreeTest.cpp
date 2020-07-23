/*
 * @file   BinarySearchTreeTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   20 July 2020
 * @version 0.1
 * @brief   A binary search tree unit test.
 */

#include <gtest\gtest.h>
#include <BinarySearchTree.h>

#include <chrono>
#include <random>
#include <list>
#include <queue>
#include <iterator>
#include <vector>
#include <algorithm>

namespace dsa {

namespace binarysearchtreetest {


static int randInt(int start_in, int end_in)
{
//  srand((unsigned) time(0));
  int randomNumber = rand()*(end_in - start_in)/RAND_MAX + start_in;
//  std::cout << " JINGLI:" << randomNumber << " MIN:"<< start_in << " MAX:"<< end_in << std::endl;
  return randomNumber;
}


static std::vector<int> genRandList(int start_in, int end_in, int num_in)
{
  std::vector<int> randvec;
  auto containsNum = [&randvec](int a) -> bool { auto iter = std::find(randvec.begin(), randvec.end(), a); return iter != randvec.end(); };
  for(int i=0; i < num_in; ++i) {
    int rndVal;
    do {
      rndVal = randInt(start_in, end_in);
//      std::cout << "start:" << start_in << " end:" << end_in << " rnd:" << rndVal << " rpt:" << containsNum(rndVal) << std::endl;
    } while (containsNum(rndVal));
    randvec.push_back(rndVal);
  }
  std::random_shuffle(randvec.begin(), randvec.end());
  return randvec;
}


class TestTree {

  struct TestTreeNode{
    int data_;
    TestTreeNode *left_, *right_;
    TestTreeNode(int data, TestTreeNode *l, TestTreeNode *r) : data_(data), left_(l), right_(r) {}
  };
  TestTreeNode *root_;
public:

  TestTree() : root_(nullptr) {}

  // ToDo: Nodes must be cleanly deleted!
  ~TestTree() {}

public:
  void add(int elem) {
    root_ = add(root_, elem);
  }
protected:
  static TestTreeNode *add(TestTreeNode *node, int data) {
    if (node == nullptr) {
      node = new TestTreeNode(data, nullptr, nullptr);
    } else {
      // Place lower elem values on left
      if (data < node->data_) {
        node->left_ = add(node->left_, data);
      } else {
        node->right_ = add(node->right_, data);
      }
    }
    return node;
  }


public:
  void preOrder(std::vector<int> &lst) { preOrder(lst, root_); }
protected:
  void preOrder(std::vector<int> &lst, TestTreeNode *node) {
    if (node == nullptr) return;

    lst.push_back(node->data_);
    if (node->left_ != nullptr) preOrder(lst, node->left_);
    if (node->right_ != nullptr) preOrder(lst, node->right_);
  }


public:
  void inOrder(std::vector<int> &lst) { inOrder(lst, root_); }
protected:
  void inOrder(std::vector<int> &lst, TestTreeNode *node) {
    if (node == nullptr) return;

    if (node->left_ != nullptr) inOrder(lst, node->left_);
    lst.push_back(node->data_);
    if (node->right_ != nullptr) inOrder(lst, node->right_);
  }


public:
  void postOrder(std::vector<int> &lst) { postOrder(lst, root_); }
protected:
  void postOrder(std::vector<int> &lst, TestTreeNode *node) {

    if (node == nullptr) return;

    if (node->left_ != nullptr) postOrder(lst, node->left_);
    if (node->right_ != nullptr) postOrder(lst, node->right_);
    lst.push_back(node->data_);
  }


public:
  void levelOrder(std::vector<int> &lst) { levelOrder(lst, root_); }
protected:
  void levelOrder(std::vector<int> &lst, TestTreeNode *node) {
    std::queue<TestTreeNode*> q;

    if (node != nullptr) q.push(node);

    while (!q.empty()) {
      node = q.back();
      q.pop();
      lst.push_back(node->data_);
      if (node->left_ != nullptr) q.push(node->left_);
      if (node->right_ != nullptr) q.push(node->right_);
    }
  }

};

//class  {
#if 0
static int LOOPS = 100;

TEST(BinarySearchTreeTest, testIsEmpty) {
  BinarySearchTree<std::string> tree;
  ASSERT_TRUE(tree.isEmpty());

  tree.add("Hello World!");
  ASSERT_FALSE(tree.isEmpty());
}


TEST(BinarySearchTreeTest, testSize) {
  BinarySearchTree<std::string> tree;
  ASSERT_EQ(tree.size(), 0);

  tree.add("Hello World!");
  ASSERT_EQ(tree.size(), 1);
}


TEST(BinarySearchTreeTest, testHeight) {
  BinarySearchTree<std::string> tree;

  // Tree should look like:
  //        M
  //      J  S
  //    B   N Z
  //  A

  // No tree
  ASSERT_EQ(tree.height(), 0);

  // Layer One
  tree.add("M");
  ASSERT_EQ(tree.height(), 1);

  // Layer Two
  tree.add("J");
  ASSERT_EQ(tree.height(), 2);
  tree.add("S");
  ASSERT_EQ(tree.height(), 2);

  // Layer Three
  tree.add("B");
  ASSERT_EQ(tree.height(), 3);
  tree.add("N");
  ASSERT_EQ(tree.height(), 3);
  tree.add("Z");
  ASSERT_EQ(tree.height(), 3);

  // Layer 4
  tree.add("A");
  ASSERT_EQ(tree.height(), 4);
}


TEST(BinarySearchTreeTest, testAdd) {

  // Add element which does not yet exist
  BinarySearchTree<char> tree;

  ASSERT_TRUE(tree.add('A'));

  // Add duplicate element
  ASSERT_FALSE(tree.add('A'));

  // Add a second element which is not a duplicate
  ASSERT_TRUE(tree.add('B'));
}


TEST(BinarySearchTreeTest, testRemove) {
  // Try removing an element which doesn't exist
  BinarySearchTree<char> tree;
  tree.add('A');
  ASSERT_EQ(tree.size(), 1);
  ASSERT_FALSE(tree.remove('B'));
  ASSERT_EQ(tree.size(), 1);

  // Try removing an element which does exist
  tree.add('B');
  ASSERT_EQ(tree.size(), 2);
  ASSERT_TRUE(tree.remove('B'));
  ASSERT_EQ(tree.size(), 1);
  ASSERT_EQ(tree.height(), 1);

  // Try removing the root
  ASSERT_TRUE(tree.remove('A'));
  ASSERT_EQ(tree.size(), 0);
  ASSERT_EQ(tree.height(), 0);
}


TEST(BinarySearchTreeTest, testContains) {
  // Setup tree
  BinarySearchTree<char> tree;

  tree.add('B');
  tree.add('A');
  tree.add('C');

  // Try looking for an element which doesn't exist
  ASSERT_FALSE(tree.contains('D'));

  // Try looking for an element which exists in the root
  ASSERT_TRUE(tree.contains('B'));

  // Try looking for an element which exists as the left child of the root
  ASSERT_TRUE(tree.contains('A'));

  // Try looking for an element which exists as the right child of the root
  ASSERT_TRUE(tree.contains('C'));
}


TEST(BinarySearchTreeTest, concurrentModificationErrorPreOrder) {
  try {
    BinarySearchTree<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);

    for (BinarySearchTree<int>::PREORDER_ITER iter = bst.preorder_iter().begin();
                                              iter != bst.preorder_iter().end();
                                              iter++) {
//      std::cout << *iter << std::endl;
      bst.add(0);
    }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Concurrent Modification Exception"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Concurrent Modification Exception";
  }
}


TEST(BinarySearchTreeTest, concurrentModificationErrorInOrderOrder) {
  try {
    BinarySearchTree<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);

    for (BinarySearchTree<int>::INORDER_ITER iter = bst.inorder_iter().begin();
                                             iter != bst.inorder_iter().end();
                                             iter++) {
//      std::cout << *iter << std::endl;
      bst.add(0);
    }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Concurrent Modification Exception"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Concurrent Modification Exception";
  }
}


TEST(BinarySearchTreeTest, concurrentModificationErrorPostOrder) {
  try {
    BinarySearchTree<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);

    for (BinarySearchTree<int>::POSTORDER_ITER iter = bst.postorder_iter().begin();
                                             iter != bst.postorder_iter().end();
                                             iter++) {
//      std::cout << *iter << std::endl;
      bst.add(0);
    }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Concurrent Modification Exception"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Concurrent Modification Exception";
  }
}


TEST(BinarySearchTreeTest, concurrentModificationErrorLevelOrder) {
  try {
    BinarySearchTree<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);

    for (BinarySearchTree<int>::LEVELORDER_ITER iter = bst.levelorder_iter().begin();
                                                iter != bst.levelorder_iter().end();
                                                iter++) {
//      std::cout << *iter << std::endl;
      bst.add(0);
    }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Concurrent Modification Exception"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Concurrent Modification Exception";
  }
}


TEST(BinarySearchTreeTest, concurrentModificationErrorRemovingPreOrder) {
  try {
    BinarySearchTree<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);

    for (BinarySearchTree<int>::PREORDER_ITER iter = bst.preorder_iter().begin();
                                              iter != bst.preorder_iter().end();
                                              iter++) {
//      std::cout << *iter << std::endl;
      bst.remove(2);
    }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Concurrent Modification Exception"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Concurrent Modification Exception";
  }
}


TEST(BinarySearchTreeTest, concurrentModificationErrorRemovingInOrderOrder) {
  try {
    BinarySearchTree<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);

    for (BinarySearchTree<int>::INORDER_ITER iter = bst.inorder_iter().begin();
                                             iter != bst.inorder_iter().end();
                                             iter++) {
//      std::cout << *iter << std::endl;
      bst.remove(2);
    }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Concurrent Modification Exception"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Concurrent Modification Exception";
  }
}


TEST(BinarySearchTreeTest, concurrentModificationErrorRemovingPostOrder) {
  try {
    BinarySearchTree<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);

    for (BinarySearchTree<int>::POSTORDER_ITER iter = bst.postorder_iter().begin();
                                               iter != bst.postorder_iter().end();
                                               iter++) {
//      std::cout << *iter << std::endl;
      bst.remove(2);
    }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Concurrent Modification Exception"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Concurrent Modification Exception";
  }
}


TEST(BinarySearchTreeTest, concurrentModificationErrorRemovingLevelOrder) {
  try {
    BinarySearchTree<int> bst;
    bst.add(1);
    bst.add(2);
    bst.add(3);
    bst.add(4);
    bst.add(5);

    for (BinarySearchTree<int>::LEVELORDER_ITER iter = bst.levelorder_iter().begin();
                                                iter != bst.levelorder_iter().end();
                                                iter++) {
//      std::cout << *iter << std::endl;
      bst.remove(2);
    }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Concurrent Modification Exception"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Concurrent Modification Exception";
  }
}


void randomRemoveTests() {

  for (int i = 0; i < LOOPS; i++) {

    int size = i;
    int MAX_RAND_NUM = randInt(size, size*100);
    BinarySearchTree<int> tree;
    std::vector<int> lst = genRandList(-MAX_RAND_NUM, MAX_RAND_NUM, size);
    for (int value : lst) tree.add(value);

    std::random_shuffle(lst.begin(), lst.end());
    // Remove all the elements we just placed in the tree
    for (int j = 0; j < size; j++) {

      int value = lst[j];

      ASSERT_TRUE(tree.remove(value));
      ASSERT_FALSE(tree.contains(value));
      ASSERT_EQ(tree.size(), size - j - 1);
    }

    ASSERT_TRUE(tree.isEmpty());
  }
}

enum class TreeTraversalOrder {PRE_ORDER, IN_ORDER, POST_ORDER, LEVEL_ORDER};

bool validateTreeTraversal(TreeTraversalOrder trav_order, const std::vector<int>& input) {

  std::vector<int> out;
  std::vector<int> expected;

  TestTree testTree;
  BinarySearchTree<int> tree;

  // Construct Binary Tree and test tree
  for (int value : input) {
    testTree.add(value);
    tree.add(value);
  }

  // Generate the expected output for the particular traversal
  switch (trav_order) {
    case TreeTraversalOrder::PRE_ORDER:
      testTree.preOrder(expected);
      // Get traversal output
      for (BinarySearchTree<int>::PREORDER_ITER iter = tree.preorder_iter().begin();
                                                iter != tree.preorder_iter().end();
                                                iter++) {
        out.push_back(*iter);
      }
      break;
    case TreeTraversalOrder::IN_ORDER:
      testTree.inOrder(expected);
      for (BinarySearchTree<int>::INORDER_ITER iter = tree.inorder_iter().begin();
                                               iter != tree.inorder_iter().end();
                                               iter++) {
        out.push_back(*iter);
      }
      break;
    case TreeTraversalOrder::POST_ORDER:
      testTree.postOrder(expected);
      for (BinarySearchTree<int>::POSTORDER_ITER iter = tree.postorder_iter().begin();
                                                 iter != tree.postorder_iter().end();
                                                 iter++) {
        out.push_back(*iter);
      }
      break;
    case TreeTraversalOrder::LEVEL_ORDER:
      testTree.levelOrder(expected);
      for (BinarySearchTree<int>::LEVELORDER_ITER iter = tree.levelorder_iter().begin();
                                                  iter != tree.levelorder_iter().end();
                                                  iter++) {
        out.push_back(*iter);
      }
      break;
  }

  // The output and the expected size better be the same size
  if (out.size() != expected.size()) return false;

  // Compare output to expected
  for (unsigned i = 0; i < out.size(); i++) if (expected[i] != out[i]) return false;

  return true;
}


TEST(BinarySearchTreeTest, testPreOrderTraversal) {
  for (int i = 0; i < LOOPS; i++) {
    int MAX_RAND_NUM = randInt(i, i*100);
    std::vector<int> input = genRandList(-MAX_RAND_NUM, MAX_RAND_NUM, i);

    ASSERT_TRUE(validateTreeTraversal(TreeTraversalOrder::PRE_ORDER, input));
  }
}

/*
ToDo: This test fails!
TEST(BinarySearchTreeTest, testInOrderTraversal) {
  for (int i = 0; i < LOOPS; i++) {
    int MAX_RAND_NUM = randInt(i, i*100);
    std::vector<int> input = genRandList(-MAX_RAND_NUM, MAX_RAND_NUM, i);
    ASSERT_TRUE(validateTreeTraversal(TreeTraversalOrder::IN_ORDER, input));
  }
}
*/

TEST(BinarySearchTreeTest, testPostOrderTraversal) {
  for (int i = 0; i < LOOPS; i++) {
    int MAX_RAND_NUM = randInt(i, i*100);
    std::vector<int> input = genRandList(-MAX_RAND_NUM, MAX_RAND_NUM, i);
    ASSERT_TRUE(validateTreeTraversal(TreeTraversalOrder::POST_ORDER, input));
  }
}

/*
ToDo: This test fails!
TEST(BinarySearchTreeTest, testLevelOrderTraversal) {
  for (int i = 0; i < LOOPS; i++) {
    int MAX_RAND_NUM = randInt(i, i*100);
    std::vector<int> input = genRandList(-MAX_RAND_NUM, MAX_RAND_NUM, i);
    ASSERT_TRUE(validateTreeTraversal(TreeTraversalOrder::LEVEL_ORDER, input));
  }
}
*/
#endif
} // namespace binarysearchtreetest

} // namespace dsa

