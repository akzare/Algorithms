/*
 * @file   QueueTest.cpp
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to C++) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   03 July 2020
 * @version 0.1
 * @brief   A queue unit test.
 */

#include <gtest\gtest.h>
#include <LinkedQueue.h>
#include <ArrayQueue.h>


#include <chrono>
#include <unistd.h>
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
using queuePtr = std::shared_ptr<Queue<T>>;

enum class QueueImpl : int { LinkedList, Array };



class QueueTest : public ::testing::Test {

protected:

  std::vector<queuePtr<int>> queues;

  QueueTest() {
	queues.push_back(std::make_shared<LinkedQueue<int>>(static_cast<int>(QueueImpl::LinkedList)));
	queues.push_back(std::make_shared<ArrayQueue<int>>(static_cast<int>(QueueImpl::Array), 10));
  }

  virtual ~QueueTest() {
	for (queuePtr<int>& queue : queues) {
      queue = nullptr;
	}
  }

  virtual void SetUp() {

  }

  virtual void TearDown() {
    for (queuePtr<int>& queue : queues) {
      queue->clear();
    }
  }

};

#if 1
TEST_F(QueueTest, testEmptyQueue) {
  for (queuePtr<int>& queue : queues) {
    ASSERT_TRUE(queue->isEmpty());
    ASSERT_EQ(queue->size(), 0);
  }
}


TEST_F(QueueTest, testPollOnEmpty) {
  try {
    for (queuePtr<int>& queue : queues) {
      queue->poll();
    }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Queue Empty"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Queue Empty";
  }

}


TEST_F(QueueTest, testPeekOnEmpty) {
  try {
    for (queuePtr<int>& queue : queues) {
      queue->peek();
    }
  }
  catch(std::runtime_error const &err) {
    EXPECT_EQ(err.what(), std::string("Queue Empty"));
  }
  catch(...) {
    FAIL() << "Expected std::runtime_error Queue Empty";
  }

}


TEST_F(QueueTest, testOffer) {
  for (queuePtr<int>& queue : queues) {
    queue->offer(2);
    EXPECT_EQ(queue->size(), 1);
  }
}


TEST_F(QueueTest, testPeek) {
  for (queuePtr<int>& queue : queues) {
    queue->offer(2);
    EXPECT_EQ(2, queue->peek());
    EXPECT_EQ(queue->size(), 1);
  }
}


TEST_F(QueueTest, testPoll) {
  for (queuePtr<int>& queue : queues) {
    queue->offer(2);
    EXPECT_EQ(2, queue->poll());
    EXPECT_EQ(queue->size(), 0);
  }
}


TEST_F(QueueTest, testExhaustively) {
  for (queuePtr<int>& queue : queues) {
    ASSERT_TRUE(queue->isEmpty());
    queue->offer(1);
    ASSERT_FALSE(queue->isEmpty());
    queue->offer(2);
    EXPECT_EQ(queue->size(), 2);
    EXPECT_EQ(1, queue->peek());
    EXPECT_EQ(queue->size(), 2);
    EXPECT_EQ(1, (int) queue->poll());
    EXPECT_EQ(queue->size(), 1);
    EXPECT_EQ(2, (int) queue->peek());
    EXPECT_EQ(queue->size(), 1);
    EXPECT_EQ(2, (int) queue->poll());
    EXPECT_EQ(queue->size(), 0);
    ASSERT_TRUE(queue->isEmpty());

  }
}
#endif

} // namespace dsa
