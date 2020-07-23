/*
 * @file   LinkListTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   03 July 2020
 * @version 0.1
 * @brief   A link list unit test.
 */

#include <gtest\gtest.h>
#include <DoublyLinkedList.h>

#include <chrono>
#include <random>
#include <list>
#include<iterator>
#include<vector>
#include <algorithm>

namespace dsa {

const int LOOPS = 10000;
const int TEST_SZ = 30;
const int NUM_NULLS = TEST_SZ / 5;
const int MAX_RAND_NUM = 250;


template <typename T>
std::vector<T> genRandList(T start_in, T end_in, int num_in)
{
  std::vector<T> randvec;

  std::random_device rd;
  std::mt19937 mt(rd());
  if (std::is_floating_point<T>::value) {
//    std::uniform_real_distribution<T> dist(start_in, end_in);
    std::uniform_real_distribution<double> dist(start_in, end_in);
    for(int i=0; i < num_in; ++i) {
      randvec.push_back(static_cast<T>(dist(mt)));
    }
  }
  else {
    std::uniform_int_distribution<T> dist(start_in, end_in);
    for(int i=0; i < num_in; ++i) {
      randvec.push_back(dist(mt));
    }
  }

  return randvec;
}


class LinkListTest : public ::testing::Test {

protected:


  DoublyLinkedList<int> *list;

  LinkListTest() {
    list = NULL;
    list = new DoublyLinkedList<int>();
  }

  virtual ~LinkListTest() {
    if (list)
      delete list;
  }

  virtual void SetUp() {

  }

  virtual void TearDown() {
    list->clear();
  }

};

#if 1
TEST_F(LinkListTest, testEmptyList) {
  EXPECT_TRUE(list->isEmpty());
  EXPECT_EQ(list->size(), 0);
}


TEST_F(LinkListTest, testRemoveFirstOfEmpty) {
  try {
    list->removeFirst();
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Empty list"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Empty list";
  }
}


TEST_F(LinkListTest, testRemoveLastOfEmpty) {
  try {
    list->removeLast();
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Empty list"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Empty list";
  }
}


TEST_F(LinkListTest, testPeekFirstOfEmpty) {
  try {
    list->peekFirst();
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Empty list"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Empty list";
  }
}


TEST_F(LinkListTest, testPeekLastOfEmpty) {
  try {
    list->peekLast();
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Empty list"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Empty list";
  }
}


TEST_F(LinkListTest, testAddFirst) {
  list->addFirst(3);
  ASSERT_EQ(list->size(), 1);
  list->addFirst(5);
  ASSERT_EQ(list->size(), 2);
}


TEST_F(LinkListTest, testAddLast) {
  list->addLast(3);
  ASSERT_EQ(list->size(), 1);
  list->addLast(5);
  ASSERT_EQ(list->size(), 2);
}


TEST_F(LinkListTest, testAddAt) {
  list->addAt(0, 1);
  ASSERT_EQ(list->size(), 1);
  list->addAt(1, 2);
  ASSERT_EQ(list->size(), 2);
  list->addAt(1, 3);
  ASSERT_EQ(list->size(), 3);
  list->addAt(2, 4);
  ASSERT_EQ(list->size(), 4);
  list->addAt(1, 8);
  ASSERT_EQ(list->size(), 5);
}


TEST_F(LinkListTest, testRemoveFirst) {
  list->addFirst(3);
  ASSERT_TRUE(list->removeFirst() == 3);
  ASSERT_TRUE(list->isEmpty());
}


TEST_F(LinkListTest, testRemoveLast) {
  list->addLast(4);
  ASSERT_TRUE(list->removeLast() == 4);
  ASSERT_TRUE(list->isEmpty());
}


TEST_F(LinkListTest, testPeekFirst) {
  list->addFirst(4);
  ASSERT_TRUE(list->peekFirst() == 4);
  ASSERT_EQ(list->size(), 1);
}


TEST_F(LinkListTest, testPeekLast) {
  list->addLast(4);
  ASSERT_TRUE(list->peekLast() == 4);
  ASSERT_EQ(list->size(), 1);
}


TEST_F(LinkListTest, testPeeking) {
  // 5
  list->addFirst(5);
  ASSERT_TRUE(list->peekFirst() == 5);
  ASSERT_TRUE(list->peekLast() == 5);

  // 6 - 5
  list->addFirst(6);
  ASSERT_TRUE(list->peekFirst() == 6);
  ASSERT_TRUE(list->peekLast() == 5);

  // 7 - 6 - 5
  list->addFirst(7);
  ASSERT_TRUE(list->peekFirst() == 7);
  ASSERT_TRUE(list->peekLast() == 5);

  // 7 - 6 - 5 - 8
  list->addLast(8);
  ASSERT_TRUE(list->peekFirst() == 7);
  ASSERT_TRUE(list->peekLast() == 8);

  // 7 - 6 - 5
  list->removeLast();
  ASSERT_TRUE(list->peekFirst() == 7);
  ASSERT_TRUE(list->peekLast() == 5);

  // 7 - 6
  list->removeLast();
  ASSERT_TRUE(list->peekFirst() == 7);
  ASSERT_TRUE(list->peekLast() == 6);

  // 6
  list->removeFirst();
  ASSERT_TRUE(list->peekFirst() == 6);
  ASSERT_TRUE(list->peekLast() == 6);
}


TEST_F(LinkListTest, testRemoving) {
  DoublyLinkedList<std::string> strs = DoublyLinkedList<std::string>();
  strs.add("a");
  strs.add("b");
  strs.add("c");
  strs.add("d");
  strs.add("e");
  strs.add("f");
  strs.remove("b");
  strs.remove("a");
  strs.remove("d");
  strs.remove("e");
  strs.remove("c");
  strs.remove("f");
  ASSERT_EQ(0, strs.size());
}


TEST_F(LinkListTest, testRemoveAt) {
  list->add(1);
  list->add(2);
  list->add(3);
  list->add(4);
  list->removeAt(0);
  list->removeAt(2);
  ASSERT_TRUE(list->peekFirst() == 2);
  ASSERT_TRUE(list->peekLast() == 3);
  list->removeAt(1);
  list->removeAt(0);
  ASSERT_EQ(list->size(), 0);
}


TEST_F(LinkListTest, testClear) {
  list->add(22);
  list->add(33);
  list->add(44);
  ASSERT_EQ(list->size(), 3);
  list->clear();
  ASSERT_EQ(list->size(), 0);
  list->add(22);
  list->add(33);
  list->add(44);
  ASSERT_EQ(list->size(), 3);
  list->clear();
  ASSERT_EQ(list->size(), 0);
}


TEST_F(LinkListTest, testRandomizedRemoving) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0, MAX_RAND_NUM);
  std::list <int> stdLinkedList;

  for (int loops = 0; loops < LOOPS; loops++) {

    list->clear();
    stdLinkedList.clear();

    std::vector<int> randNums = genRandList<int>(0, MAX_RAND_NUM, TEST_SZ);
    for (const int& value : randNums) {
      stdLinkedList.push_back(value);
      list->add(value);
    }

    std::random_shuffle(randNums.begin(), randNums.end());

    for (std::vector<int>::iterator ptr = randNums.begin(); ptr < randNums.end(); ptr++) {

      int rm_val = *ptr;

      stdLinkedList.remove(rm_val);
      ASSERT_EQ(true, list->remove(rm_val));
      ASSERT_EQ(stdLinkedList.size(), list->size());

      DoublyLinkedList<int>::Iterator iter2 = list->begin();
      for (std::list<int>::iterator iter1 = stdLinkedList.begin();	iter1 != stdLinkedList.end(); iter1++) {
        ASSERT_EQ(*iter1, *iter2++);
      }

      iter2 = list->begin();
      for (std::list<int>::iterator iter1 = stdLinkedList.begin();	iter1 != stdLinkedList.end(); iter1++) {
        ASSERT_EQ(*iter1, *iter2++);
      }
    }

    list->clear();
    stdLinkedList.clear();

    for (const int& value : randNums) {
      stdLinkedList.push_back(value);
      list->add(value);
    }

    // Try removing elements whether or not they exist
    for (std::vector<int>::iterator ptr = randNums.begin(); ptr < randNums.end(); ptr++) {

      int rm_val = static_cast<int>(dist(mt));
      stdLinkedList.remove(rm_val);
      list->remove(rm_val);
      ASSERT_EQ(stdLinkedList.size(), list->size());

      DoublyLinkedList<int>::Iterator iter2 = list->begin();
      for (std::list<int>::iterator iter1 = stdLinkedList.begin();	iter1 != stdLinkedList.end(); iter1++) {
        ASSERT_EQ(*iter1, *iter2++);
      }
    }
  }
}


TEST_F(LinkListTest, testRandomizedIndexOf) {
  std::list<int> stdLinkedList;

  for (int loops = 0; loops < LOOPS; loops++) {

    stdLinkedList.clear();
    list->clear();

    std::vector<int> randNums = genRandList<int>(0, MAX_RAND_NUM, TEST_SZ);
    for (const int& value : randNums) {
      stdLinkedList.push_back(value);
      list->add(value);
    }

    std::random_shuffle(randNums.begin(), randNums.end());

    for (std::vector<int>::iterator ptr = randNums.begin(); ptr < randNums.end(); ptr++) {
      int elem = *ptr;
      int index1 = -1;

  	  auto itr = std::find(stdLinkedList.begin(), stdLinkedList.end(), elem);
  	  if (itr != stdLinkedList.end()) {
  		index1 = std::distance(stdLinkedList.begin(), itr);
      }
      int index2 = list->indexOf(elem);

      ASSERT_EQ(index1, index2);
      ASSERT_EQ(stdLinkedList.size(), list->size());

      DoublyLinkedList<int>::Iterator iter2 = list->begin();
      for (std::list<int>::iterator iter1 = stdLinkedList.begin();	iter1 != stdLinkedList.end(); iter1++) {
        ASSERT_EQ(*iter1, *iter2++);
      }
    }
  }
}


TEST_F(LinkListTest, testToString) {
  DoublyLinkedList<std::string> strs = DoublyLinkedList<std::string>();

  ASSERT_EQ(strs.toString(), "[  ]");
  strs.add("a");
  ASSERT_EQ(strs.toString(), "[ a ]");
  strs.add("b");
  ASSERT_EQ(strs.toString(), "[ a, b ]");
  strs.add("c");
  strs.add("d");
  strs.add("e");
  strs.add("f");
  ASSERT_EQ(strs.toString(), "[ a, b, c, d, e, f ]");
//  std::cout << strs << std::endl;
}


TEST_F(LinkListTest, testReverse) {
  list->addFirst(20);
  list->addFirst(4);
  list->addFirst(15);
  list->addFirst(85);

  std::cout << "Given linked list\n";
  std::cout << *list << std::endl;

  list->reverse();

  std::cout << "\nReversed Linked list \n";
  std::cout << *list << std::endl;

  ASSERT_EQ(list->peekFirst(), 20);
  ASSERT_EQ(list->peekLast(), 85);

  list->removeLast();
  ASSERT_EQ(list->peekFirst(), 20);
  ASSERT_EQ(list->peekLast(), 15);

  list->removeLast();
  ASSERT_EQ(list->peekFirst(), 20);
  ASSERT_EQ(list->peekLast(), 4);

}

#endif
} // namespace dsa
