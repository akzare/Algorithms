'''
 * @file   QuickSort3.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   Quick sort implementation
 * QuickSort3 or Dutch National Flag algorithm is similar to the QuickSort algorithm but has an
 * improved partitioning algorithm. QuickSort is quite slow in the case where very few unique
 * elements exist in the array so the QuickSort3 algorithm is used at that time.
'''

import sys
import random

class QuickSort3():
  """
  Mergesort implements InplaceSort for ease of testings, but in reality
  it is not really a good fit for an inplace sorting algorithm.
  """
  def __init__(self):
    pass


  def sort(self, values):
    if values == None: 
      return
    self.quickSort3(values)


  def quickSort3(self, ar):
    self.randomizedQuickSort(ar, 0, len(ar) - 1)


  def partition3(self, a, l, r):
    """
    partiton array in such a way that all the elements whose value is equal to
    pivot are grouped together
    """
    j = 0
    k = 0
    if r - l <= 1:
      if a[r] < a[l]:
        self.swap(a, l, r)

      j = l
      k = r
      m = [j, k]
      return m

    mid = l
    p = a[r]
    while mid <= r:
      if a[mid] < p:
        self.swap(a, l, mid)
        l += 1
        mid += 1
      elif a[mid] == p:
        mid += 1
      else:
        self.swap(a, mid, r)
        r -= 1

    j = l - 1
    k = mid
    m = [j, k]
    return m

  
  def randomizedQuickSort(self, a, l, r):
    """
    Sort interval [lo, hi] inplace recursively
    This chooses random pivot value thus improving time complexity
    """
    if l >= r:
      return

    k = random.randint(0, r - l + 1) + 1
    t = a[l]
    a[l] = a[k]
    a[k] = t
    # use partition3
    m = self.partition3(a, l, r)
    self.randomizedQuickSort(a, l, m[0])
    self.randomizedQuickSort(a, m[1], r)


  def swap(self, ar, i, j):
    tmp = ar[i]
    ar[i] = ar[j]
    ar[j] = tmp



if __name__ == '__main__':
  """
  Example usage
  """
  sorter = QuickSort3()
  array = [10, 4, 6, 4, 8, -13, 2, 3]
  sorter.sort(array)
  # Prints:
  # [-13, 2, 3, 4, 4, 6, 8, 10]
  print(array)
