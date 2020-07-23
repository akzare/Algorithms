'''
 * @file   BitManipulationsTest.py
 * @author (original JAVA) Micah Stairs
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   A BitManipulations unit test.
'''

import unittest
from collections import deque
import random
from BitManipulations import BitManipulations

class BitManipulationsTest(unittest.TestCase):

  def setUp(self):
    self.bm = BitManipulations()



  def test_SetBit(self):
    self.assertEqual(self.bm.setBit(0, 0), 0b1)
    self.assertEqual(self.bm.setBit(0, 1), 0b10)
    self.assertEqual(self.bm.setBit(0, 2), 0b100)
    self.assertEqual(self.bm.setBit(0, 3), 0b1000)
    self.assertEqual(self.bm.setBit(0, 4), 0b10000)
    self.assertEqual(self.bm.setBit(0, 5), 0b100000)



  def test_PowerOfTwo(self):
    self.assertFalse(self.bm.isPowerOfTwo(0))
    self.assertFalse(self.bm.isPowerOfTwo(-1))
    self.assertFalse(self.bm.isPowerOfTwo(7))
    self.assertFalse(self.bm.isPowerOfTwo(9))
    self.assertFalse(self.bm.isPowerOfTwo(123456789))

    self.assertTrue(self.bm.isPowerOfTwo(1))
    self.assertTrue(self.bm.isPowerOfTwo(2))
    self.assertTrue(self.bm.isPowerOfTwo(4))
    self.assertTrue(self.bm.isPowerOfTwo(2048))
    self.assertTrue(self.bm.isPowerOfTwo(1 << 20))



  def test_ClearBit(self):
    self.assertEqual(self.bm.clearBit(0b0000, 1), 0)
    self.assertEqual(self.bm.clearBit(0b0100, 2), 0)
    self.assertEqual(self.bm.clearBit(0b0001, 0), 0)
    self.assertEqual(self.bm.clearBit(0b1111, 0), 14)


if __name__ == '__main__':
  unittest.main()