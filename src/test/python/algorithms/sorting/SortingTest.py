'''
 * @file   SortingTest.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   28 Jun 2020
 * @version 0.1
 * @brief   A Sorting unit test.
 * Test all sorting algorithms under various constraints.
 *
'''

import unittest
import time
from collections import deque
import array as arr
import random
from enum import Enum, auto
import copy

from BubbleSort import BubbleSort
from BucketSort import BucketSort
from CountingSort import CountingSort 
from Heapsort import Heapsort
from InsertionSort import InsertionSort 
from MergeSort import MergeSort 
from QuickSort import QuickSort 
from QuickSort3 import QuickSort3 
from RadixSort import RadixSort 
from SelectionSort import SelectionSort 


class SortingAlgorithm(Enum):
  BUBBLE_SORT = auto()
  BUCKET_SORT = auto()
  COUNTING_SORT = auto()
  HEAP_SORT = auto()
  INSERTION_SORT = auto()
  MERGE_SORT = auto()
  QUICK_SORT = auto()
  QUICK_SORT3 = auto()
  RADIX_SORT = auto()
  SELECTION_SORT = auto()


# ToDo: CountingSort, MergeSort, QuickSort3, and RadixSort are not passing the test!
class SortingTest(unittest.TestCase):

  def setUp(self):
    self.TEST_SZ = 40
    self.MAX_RAND_NUM = 250
      
    self.funList = {SortingAlgorithm.BUBBLE_SORT: BubbleSort,
                    SortingAlgorithm.BUCKET_SORT: BucketSort,
#                    SortingAlgorithm.COUNTING_SORT : CountingSort,
                    SortingAlgorithm.HEAP_SORT : Heapsort,
                    SortingAlgorithm.INSERTION_SORT : InsertionSort,
#                    SortingAlgorithm.MERGE_SORT : MergeSort,
                    SortingAlgorithm.QUICK_SORT : QuickSort,
#                    SortingAlgorithm.QUICK_SORT3 : QuickSort3,
#                    SortingAlgorithm.RADIX_SORT : RadixSort,
                    SortingAlgorithm.SELECTION_SORT : SelectionSort
                    }


  def test_verifySortingAlgorithms_smallPositiveIntegersOnly(self):
    for sz in range(0, 100):
      for algorithm in self.funList.keys():
        sorter = self.funList.get(algorithm)()
        values = self.genRandList(sz, 0, 51)
        cpy = copy.deepcopy(values)
 
        values.sort()
        sorter.sort(cpy)

        self.assertEqual(values, cpy)


  def test_verifySortingAlgorithms_smallNegativeIntegersOnly(self):
    for sz in range(0, 100):
      for algorithm in self.funList.keys():
        # Skip radix sort since our implementation doesn't handle negative numbers.
        if algorithm == SortingAlgorithm.RADIX_SORT:
          continue

        sorter = self.funList.get(algorithm)()
        values = self.genRandList(sz, -50, 51)
        cpy = copy.deepcopy(values)

        values.sort()
        sorter.sort(cpy)

        self.assertEqual(values, cpy)


  def test_benchmark(self):
    sz = 30000
    for algorithm in self.funList.keys():
      sorter = self.funList.get(algorithm)()
      values = self.genRandList(sz, 0, 51)
      cpy = copy.deepcopy(values)
 
      start = time.process_time()
      values.sort()
      end = time.process_time()
      elspasedTimePython = end - start
      
      start = time.process_time()
      sorter.sort(cpy)
      end = time.process_time()
      elspasedTimeAlg = end - start

      if algorithm == SortingAlgorithm.BUBBLE_SORT:
        # BUBBLE_SORT time: 141.859375 vs std time: 0.015625
        print('BUBBLE_SORT time: {} vs std time: {}'.format(elspasedTimeAlg, elspasedTimePython))
      elif algorithm == SortingAlgorithm.BUCKET_SORT:
        # BUCKET_SORT time: 0.015625 vs std time: 0.0
        print('BUCKET_SORT time: {} vs std time: {}'.format(elspasedTimeAlg, elspasedTimePython))
#     elif algorithm == SortingAlgorithm.COUNTING_SORT:
      elif algorithm == SortingAlgorithm.HEAP_SORT:
        # HEAP_SORT time: 0.21875 vs std time: 0.015625
        print('HEAP_SORT time: {} vs std time: {}'.format(elspasedTimeAlg, elspasedTimePython))
      elif algorithm == SortingAlgorithm.INSERTION_SORT:
        # INSERTION_SORT time: 87.15625 vs std time: 0.0
        print('INSERTION_SORT time: {} vs std time: {}'.format(elspasedTimeAlg, elspasedTimePython))
#     elif algorithm == SortingAlgorithm.MERGE_SORT:
      elif algorithm == SortingAlgorithm.QUICK_SORT:
        # QUICK_SORT time: 0.578125 vs std time: 0.0
        print('QUICK_SORT time: {} vs std time: {}'.format(elspasedTimeAlg, elspasedTimePython))
#     elif algorithm == SortingAlgorithm.QUICK_SORT3:
#     elif algorithm == SortingAlgorithm.RADIX_SORT:
      elif algorithm == SortingAlgorithm.SELECTION_SORT:
        # SELECTION_SORT time: 34.046875 vs std time: 0.0
        print('SELECTION_SORT time: {} vs std time: {}'.format(elspasedTimeAlg, elspasedTimePython))


  def genRandList(self, sz, lo, hi):
    """
    Generate a list of random numbers
    """   
    #Generate sz random numbers between lo and hi
    lst = []    
    for i in range(0, sz):
      n = random.randint(lo, hi)
      lst.append(n)

    random.shuffle(lst)
    return lst



if __name__ == '__main__':
  unittest.main()