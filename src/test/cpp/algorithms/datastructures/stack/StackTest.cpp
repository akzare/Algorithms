/*
 * @file   StckTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   03 July 2020
 * @version 0.1
 * @brief   A stack unit test.
 */

#include <gtest\gtest.h>
#include <ListStack.h>
#include <ArrayStack.h>


#include <chrono>
#include <unistd.h>
#include <random>
#include <list>
#include <iterator>
#include <vector>
#include <algorithm>

namespace dsa {

const int LOOPS = 10000;
const int TEST_SZ = 30;
const int NUM_NULLS = TEST_SZ / 5;
const int MAX_RAND_NUM = 250;

template <typename T>
using stackPtr = std::shared_ptr<Stack<T>>;

enum class StackImpl : int { LinkedList, Array };

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


class StackTest : public ::testing::Test {

protected:

  std::vector<stackPtr<int>> stacks;

  StackTest() {
    stacks.push_back(std::make_shared<ListStack<int>>(static_cast<int>(StackImpl::LinkedList)));
    stacks.push_back(std::make_shared<ArrayStack<int>>(static_cast<int>(StackImpl::Array)));
  }

  virtual ~StackTest() {
	for (stackPtr<int>& stack : stacks) {
      stack = nullptr;
	}
  }

  virtual void SetUp() {

  }

  virtual void TearDown() {
    for (stackPtr<int>& stack : stacks) {
      stack->clear();
    }
  }

};

#if 1
TEST_F(StackTest, testEmptyStack) {

  for (stackPtr<int>& stack : stacks) {
    ASSERT_TRUE(stack->isEmpty());
    ASSERT_EQ(stack->size(), 0);
  }
}


TEST_F(StackTest, testPopOnEmpty) {
  try {
    for (stackPtr<int>& stack : stacks) {
      stack->pop();
    }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Empty Stack"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Empty Stack";
  }
}


TEST_F(StackTest, testPeekOnEmpty) {
  try {
    for (stackPtr<int>& stack : stacks) {
      stack->peek();
    }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Empty Stack"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Empty Stack";
  }
}


TEST_F(StackTest, testPush) {
  for (stackPtr<int>& stack : stacks) {
    stack->push(2);
    EXPECT_EQ(stack->size(), 1);
  }
}


TEST_F(StackTest, testPeek) {
  for (stackPtr<int>& stack : stacks) {
    stack->push(2);
    EXPECT_EQ(2, stack->peek());
    EXPECT_EQ(stack->size(), 1);
  }
}


TEST_F(StackTest, testPop) {
  for (stackPtr<int>& stack : stacks) {
    stack->push(2);
    EXPECT_EQ(2, stack->pop());
    EXPECT_EQ(stack->size(), 0);
  }
}


TEST_F(StackTest, testExhaustively) {
  for (stackPtr<int>& stack : stacks) {
	ASSERT_TRUE(stack->isEmpty());
    stack->push(1);
    ASSERT_FALSE(stack->isEmpty());
    stack->push(2);
    EXPECT_EQ(stack->size(), 2);
    EXPECT_EQ(2, (int) stack->peek());
    EXPECT_EQ(stack->size(), 2);
    EXPECT_EQ(2, (int) stack->pop());
    EXPECT_EQ(stack->size(), 1);
    EXPECT_EQ(1, (int) stack->peek());
    EXPECT_EQ(stack->size(), 1);
    EXPECT_EQ(1, (int) stack->pop());
    EXPECT_EQ(stack->size(), 0);
    ASSERT_TRUE(stack->isEmpty());
  }
}


TEST_F(StackTest, benchMarkTest) {
  int n = 10000000;
  for (stackPtr<int>& stack : stacks) {

    switch (stack->id())
    {
	  case static_cast<int>(StackImpl::LinkedList):
        std::cout << "Benchmark: LinkedList implementation : " << std::endl; // 2600 ms
	    break;
	  case static_cast<int>(StackImpl::Array):
        std::cout << "Benchmark: Array implementation : " << std::endl; // 1162 ms
	    break;
      default:
  	    break;
    }

	auto start = std::chrono::steady_clock::now();

	for(int i=0; i < n; ++i) stack->push(1);
	for(int i=0; i < n; ++i) stack->pop();

	auto end = std::chrono::steady_clock::now();

#if 0
	std::cout << "Elapsed time in nanoseconds : "
		<< std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
		<< " ns" << std::endl;

	std::cout << "Elapsed time in microseconds : "
		<< std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
		<< " µs" << std::endl;
#endif
	std::cout << "Elapsed time in milliseconds : "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
		<< " ms" << std::endl;

	std::cout << "Elapsed time in seconds : "
		<< std::chrono::duration_cast<std::chrono::seconds>(end - start).count()
		<< " sec";

  }
}

#endif
} // namespace dsa
