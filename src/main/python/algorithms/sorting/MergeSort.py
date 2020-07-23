'''
 * @file   MergeSort.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   27 Jun 2020
 * @version 0.1
 * @brief   Merge sort implementation
'''

import sys

class MergeSort():
  """
  Mergesort implements InplaceSort for ease of testings, but in reality
  it is not really a good fit for an inplace sorting algorithm.
  """

  def __init__(self):
    pass


  def sort(self, values):
    return self.mergesort(values)


  def mergesort(self, ar):
    """  
    Base case is when a single element (which is already sorted)
    """
    n = len(ar)
    if n <= 1:
      return ar

    # Split array into two parts and recursively sort them
    left = self.mergesort(ar[:n // 2])
    right = self.mergesort(ar[n // 2::])

    # Combine the two arrays into one larger array
    return self.merge(left, right)


  def merge(self, ar1, ar2):
    """
    Merge two sorted arrays into a larger sorted array
    """
    n1 = len(ar1) 
    n2 = len(ar2)
    n = n1 + n2 
    i1 = 0 
    i2 = 0
    ar = [0]*n

    for i in range(0, n):
      if i1 == n1:
        ar[i] = ar2[i2]
        i2 += 1
      elif i2 == n2:
        ar[i] = ar1[i1]
        i1 += 1
      else:
        if ar1[i1] < ar2[i2]:
          ar[i] = ar1[i1]
          i1 += 1
        else:
          ar[i] = ar2[i2]
          i2 += 1

    return ar



if __name__ == '__main__':
  """
  Example usage
  """
  array = [10, 4, 6, 4, 8, -13, 2, 3]
  sorter = MergeSort()
  array = sorter.sort(array)
  # Prints:
  # [-13, 2, 3, 4, 4, 6, 8, 10]
  print(array)
