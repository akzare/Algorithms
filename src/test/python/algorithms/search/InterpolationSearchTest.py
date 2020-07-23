'''
 * @file   InterpolationSearchTest.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   An InterpolationSearch unit test.
'''

import unittest
from collections import deque
import random
from InterpolationSearch import InterpolationSearch

class InterpolationSearchTest(unittest.TestCase):

  def setUp(self):
    self.s = InterpolationSearch()


  def test_Coverage1(self):
    arr = [0, 1, 2, 3, 4, 5]
    index = self.s.interpolationSearch(arr, 2)
    self.assertTrue(index == 2)


  def test_Coverage2(self):
    arr = [0, 1, 2, 3, 4, 5]
    index = self.s.interpolationSearch(arr, 5)
    self.assertTrue(index == 5)


  def testCoverage3(self):
    arr = [0, 1, 2, 3, 4, 5]
    index = self.s.interpolationSearch(arr, -1)
    self.assertTrue(index == -1)


  def testCoverage4(self):
    arr = [0, 1, 2, 3, 4, 5]
    index = self.s.interpolationSearch(arr, 8)
    self.assertTrue(index == -1)



if __name__ == '__main__':
  unittest.main()