'''
 * @file   IntQueueTest.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   23 Jun 2020
 * @version 0.1
 * @brief   An IntQueue unit test.
'''

import unittest
from collections import deque
import array as arr
import random
from LinkedQueue import LinkedQueue
from ArrayQueue import ArrayQueue
from IntQueue import IntQueue


class IntQueueTest(unittest.TestCase):

  def setUp(self):
    pass


  def test_EmptyQueue(self):
    queue = IntQueue(2)
    self.assertTrue(queue.isEmpty())
    self.assertEqual(queue.size(), 0)


  def test_offerOneElement(self):
    queue = IntQueue(1)
    queue.offer(77)
    self.assertEqual(queue.size(), 1)


  def test_All(self):
    n = 5
    queue = IntQueue(10)
    self.assertTrue(queue.isEmpty())
    for i in range(1, n+1):
      queue.offer(i)
      self.assertFalse(queue.isEmpty())

    for i in range(1, n+1):
      self.assertEqual(i, int(queue.peek()))
      self.assertEqual(i, int(queue.poll()))
      self.assertEqual(queue.size(), n - i)

    self.assertTrue(queue.isEmpty())
    n = 8
    for i in range(1, n+1):
      queue.offer(i)
      self.assertFalse(queue.isEmpty())

    for i in range(1, n+1):
      self.assertEqual(i, int(queue.peek()))
      self.assertEqual(i, int(queue.poll()))
      self.assertEqual(queue.size(), n - i)

    self.assertTrue(queue.isEmpty())
    n = 9;
    for i in range(1, n+1):
      queue.offer(i)
      self.assertFalse(queue.isEmpty())

    for i in range(1, n+1):
      self.assertEqual(i, int(queue.peek()))
      self.assertEqual(i, int(queue.poll()))
      self.assertEqual(queue.size(), n - i)

    self.assertTrue(queue.isEmpty())
    n = 10
    for i in range(1, n+1):
      queue.offer(i)
      self.assertFalse(queue.isEmpty())

    for i in range(1, n+1):
      self.assertEqual(i, int(queue.peek()))
      self.assertEqual(i, int(queue.poll()))
      self.assertEqual(queue.size(), n - i);

    self.assertTrue(queue.isEmpty())


  def test_PeekOneElement(self):
    queue = IntQueue(1)
    queue.offer(77)
    self.assertTrue(queue.peek() == 77)
    self.assertEqual(queue.size(), 1)


  def test_pollOneElement(self):
    queue = IntQueue(1)
    queue.offer(77)
    self.assertTrue(queue.poll() == 77)
    self.assertEqual(queue.size(), 0)


  def test_Random(self):
    for qSize in range(1, 51):
      intQ = IntQueue(qSize)
      arrayDeque = deque()

      self.assertEqual(len(arrayDeque) == 0, intQ.isEmpty())
      self.assertEqual(len(arrayDeque), intQ.size())

      for operations in range(0, 5000):
        r = random.random()

        if r < 0.60:
          elem = random.randrange(1000)
          if len(arrayDeque) < qSize:
            arrayDeque.append(elem)
            intQ.offer(elem)

        else:
          if len(arrayDeque) != 0:
            self.assertEqual(int(arrayDeque.popleft()), int(intQ.poll()))

        self.assertEqual(len(arrayDeque) == 0, intQ.isEmpty())
        self.assertEqual(len(arrayDeque), intQ.size())

if __name__ == '__main__':
  unittest.main()