'''
 * @file   Heapsort.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   27 Jun 2020
 * @version 0.1
 * @brief   heap sort implementation
'''

import sys

class Heapsort():

  def __init__(self):
    pass


  def sort(self, values):
    self.heapsort(values)


  def heapsort(self, ar):
    if ar == None:
      return None
    n = len(ar)

    # Heapify, converts array into binary heap O(n), see:
    # http://www.cs.umd.edu/~meesh/351/mount/lectures/lect14-heapsort-analysis-part.pdf
    for i in range(max(0, (n // 2) - 1), -1, -1):
      self.sink(ar, n, i)

    # Sorting bit
    for i in range(n - 1, -1, -1):
      self.swap(ar, 0, i)
      self.sink(ar, i, 0)



  def sink(self, ar, n, i):
    while True:
      left = 2 * i + 1 # Left  node
      right = 2 * i + 2 # Right node
      largest = i

      # Right child is larger than parent
      if right < n and ar[right] > ar[largest]:
        largest = right

      # Left child is larger than parent
      if left < n and ar[left] > ar[largest]:
        largest = left

      # Move down the tree following the largest node
      if largest != i:
        self.swap(ar, largest, i)
        i = largest
      else:
        break


  def swap(self, ar, i, j):
    tmp = ar[i]
    ar[i] = ar[j]
    ar[j] = tmp



if __name__ == '__main__':
  """
  Example usage
  """
  sorter = Heapsort()
  array = [10, 4, 6, 4, 8, -13, 2, 3]
  sorter.sort(array)
  # Prints:
  # [-13, 2, 3, 4, 4, 6, 8, 10]
  print(array)
