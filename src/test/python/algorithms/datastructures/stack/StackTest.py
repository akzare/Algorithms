'''
 * @file   StackTest.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   23 Jun 2020
 * @version 0.1
 * @brief   A stack unit test.
'''

import unittest
from collections import deque
import array as arr
import random
from ListStack import ListStack
from ArrayStack import ArrayStack
from IntStack import IntStack



class StackTest(unittest.TestCase):


  def setUp(self):   
    self.stacks = []
    self.stacks.append(ListStack())   
    self.stacks.append(ArrayStack(0))   
    self.stacks.append(IntStack(2))   


  def tearDown(self):
    for stack in self.stacks:      
      while not stack.isEmpty():  
        stack.pop()


  def test_EmptyStack(self):
    for stack in self.stacks:
      self.assertTrue(stack.isEmpty());
      self.assertEqual(stack.size(), 0);


  def test_PopOnEmpty(self):
    for stack in self.stacks:
      with self.assertRaises(Exception):
        stack.pop()


  def test_PeekOnEmpty(self):
    for stack in self.stacks:
      with self.assertRaises(Exception):
        stack.peek()


  def test_Push(self):
    for stack in self.stacks:
      stack.push(2)
      self.assertEqual(stack.size(), 1)


  def test_Peek(self):
    for stack in self.stacks:
      stack.push(2)
      self.assertEqual(2, int(stack.peek()))
      self.assertEqual(stack.size(), 1)


  def test_Pop(self):
    for stack in self.stacks:
      stack.push(2);
      self.assertEqual(2, int(stack.pop()))
      self.assertEqual(stack.size(), 0);



  def test_Exhaustively(self):
    for stack in self.stacks:
      self.assertTrue(stack.isEmpty())
      stack.push(1)
      self.assertFalse(stack.isEmpty())
      stack.push(2)
      self.assertEqual(stack.size(), 2)
      self.assertEqual(2, int(stack.peek()))
      self.assertEqual(stack.size(), 2)
      self.assertEqual(2, int(stack.pop()))
      self.assertEqual(stack.size(), 1)
      self.assertEqual(1, int(stack.peek()))
      self.assertEqual(stack.size(), 1)
      self.assertEqual(1, int(stack.pop()))
      self.assertEqual(stack.size(), 0)
      self.assertTrue(stack.isEmpty())


if __name__ == '__main__':
  unittest.main()