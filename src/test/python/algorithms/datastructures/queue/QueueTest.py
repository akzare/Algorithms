'''
 * @file   QueueTest.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   23 Jun 2020
 * @version 0.1
 * @brief   A queue unit test.
'''

import unittest
from collections import deque
import array as arr
import random
from LinkedQueue import LinkedQueue
from ArrayQueue import ArrayQueue
from IntQueue import IntQueue


class QueueTest(unittest.TestCase):

  def setUp(self):
    self.queues = []
    self.queues.append(LinkedQueue())   
    self.queues.append(ArrayQueue(0, 3))   
    self.queues.append(IntQueue(2))   


  def tearDown(self):
    for queue in self.queues:      
      while not queue.isEmpty():  
        queue.poll()


  def test_EmptyQueue(self):
    for queue in self.queues:      
      self.assertTrue(queue.isEmpty())
      self.assertEqual(queue.size(), 0)


  def test_PollOnEmpty(self):
    for queue in self.queues:
      with self.assertRaises(Exception):
        queue.poll()


  def test_PeekOnEmpty(self):
    for queue in self.queues:    
      with self.assertRaises(Exception):
        queue.peek()


  def test_Offer(self):
    for queue in self.queues:
      queue.offer(2)
      self.assertEqual(queue.size(), 1)


  def test_Peek(self):
    for queue in self.queues:
      queue.offer(2);
      self.assertEqual(2, int(queue.peek()))
      self.assertEqual(queue.size(), 1)


  def test_Poll(self):
    for queue in self.queues:
      queue.offer(2)
      self.assertEqual(2, int(queue.poll()))
      self.assertEqual(queue.size(), 0)


  def test_Exhaustively(self):
    for queue in self.queues:
      self.assertTrue(queue.isEmpty())
      queue.offer(1)
      self.assertFalse(queue.isEmpty())
      queue.offer(2)
      self.assertEqual(queue.size(), 2)
      self.assertEqual(1, int(queue.peek()))
      self.assertEqual(queue.size(), 2)
      self.assertEqual(1, int(queue.poll()))
      self.assertEqual(queue.size(), 1)
      self.assertEqual(2, int(queue.peek()))
      self.assertEqual(queue.size(), 1)
      self.assertEqual(2, int(queue.poll()))
      self.assertEqual(queue.size(), 0)
      self.assertTrue(queue.isEmpty())


if __name__ == '__main__':
  unittest.main()