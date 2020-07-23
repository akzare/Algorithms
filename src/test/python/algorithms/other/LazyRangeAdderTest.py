'''
 * @file   LazyRangeAdderTest.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   30 Jun 2020
 * @version 0.1
 * @brief   LazyRangeAdderTest unit test.
'''

import unittest
import copy
from collections import deque
import array as arr
import random
from LazyRangeAdder import LazyRangeAdder


class LazyRangeAdderTest(unittest.TestCase):

  def setUp(self):
    pass


  def test_rangeUpdateTest1(self):
    la = LazyRangeAdder()
    a = [10, 5, 20, 40]
    la.lazyRangeAdder(a)
    la.add(0, 1, 10)
    la.add(1, 3, 20)
    la.add(2, 2, 30)
    la.done()
    expected = [20, 35, 70, 60]
    self.assertEqual(expected, a)



  def test_rangeUpdateTest2(self):
    la = LazyRangeAdder()
    a = [270, 311, 427, 535, 334, 193, 174]
    la.lazyRangeAdder(a)
    la.add(2, 5, 32)
    la.add(0, 4, 101)
    la.add(5, 6, -73)
    la.done()
    expected = [371, 412, 560, 668, 467, 152, 101]
    self.assertEqual(expected, a)



  def test_randomRangeAdditionTests(self):
    """
    Try several different array sizes
    """
    la = LazyRangeAdder()    
    for n in range(1, 1000):

      arr1 = [0]*n
      self.randomFill(arr1)
      arr2 = copy.deepcopy(arr1)

      la.lazyRangeAdder(arr1)

      # Do 50 random range adds
      for i in range(0, 50):
        # Generate a random range
        l = self.randValue(0, n)
        r = self.randValue(0, n)
        l = min(l, r)
        r = max(l, r)

        x = self.randValue(-100, 100)
        la.add(l, r, x)
        self.slowRangeAdd(arr2, l, r, x)

      la.done()

      self.assertEqual(arr1, arr2)



  def slowRangeAdd(self, arr, l, r, x):
    """
    Adds `x` to the range [l, r] in arr
    """
    for i in range(l, r+1):
      arr[i] += x



  def randomFill(self, arr):
    for i in range(0, len(arr)):
      arr[i] = self.randValue(0, 1000)



  def randValue(self, min, max):
    """
    Generates a random number between [min, max)
    """
    return min + int(random.random() * ((max - min)))



if __name__ == '__main__':
  unittest.main()