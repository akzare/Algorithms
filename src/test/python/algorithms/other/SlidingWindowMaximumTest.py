'''
 * @file   SlidingWindowMaximumTest.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   30 Jun 2020
 * @version 0.1
 * @brief   SlidingWindowMaximumTest unit test.
'''

import unittest
import copy
from collections import deque
import array as arr
import random
import sys
from SlidingWindowMaximum import SlidingWindowMaximum


class SlidingWindowMaximumTest(unittest.TestCase):

  def setUp(self):
    self.TESTS = 1500


  def test_smallWindowTest(self):

    values = [1, 2, 1, 3, 0, 4]
    w = SlidingWindowMaximum(values)

    w.advance()
    self.assertEqual(1, w.getMax())
    w.advance()
    self.assertEqual(2, w.getMax())
    w.advance()
    self.assertEqual(2, w.getMax())
    w.shrink()
    self.assertEqual(2, w.getMax())
    w.shrink()
    self.assertEqual(1, w.getMax())
    w.advance()
    self.assertEqual(3, w.getMax())
    w.advance()
    self.assertEqual(3, w.getMax())
    w.advance()
    self.assertEqual(4, w.getMax())
    w.shrink()
    self.assertEqual(4, w.getMax())
    w.shrink()
    self.assertEqual(4, w.getMax())
    w.shrink()
    self.assertEqual(4, w.getMax())



  def test_randomizedSlidingWindowTest(self):
    for sz in range(1, self.TESTS + 1):
      self.randomizedTest(sz)



  def fillRandom(self, ar):
    for i in range(0, len(ar)):
      if random.random() < 0.5:
        ar[i] = int(random.random() * 25)
      else:
        ar[i] = int(random.random() * -25)



  def randomizedTest(self, n):

    r = max(0.1, random.random())
    ar = [0]*n;
    self.fillRandom(ar)

    window = SlidingWindowMaximum(ar)
    lo = 0 
    hi = 0
    while hi < n:

      # increase hi
      if random.random() < r:
        window.advance()
        hi += 1

        # increase lo if we can
      else:
        if lo + 1 < hi:
          lo += 1
          window.shrink()

      # Ignore invalid queries
      if window.lo == window.hi: 
        continue

      # Manually find the window maximum
      maxVal = -sys.maxsize - 1
      for i in range(lo, hi):
        maxVal = max(maxVal, ar[i])
#      print("ar= ", ar)
#      print("lo= ", lo)
#      print("hi= ", hi)

      self.assertEqual(maxVal, window.getMax())




if __name__ == '__main__':
  unittest.main()