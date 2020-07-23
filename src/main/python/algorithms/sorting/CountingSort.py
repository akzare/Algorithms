'''
 * @file   CountingSort.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   27 Jun 2020
 * @version 0.1
 * @brief   Counting sort implementation
'''

import sys

class CountingSort():

  def __init__(self):
    pass


  def sort(self, values):
    minValue = sys.maxsize
    maxValue = -sys.maxsize - 1
    for i in range(0, len(values)):
      if values[i] < minValue:
        minValue = values[i]
      if values[i] > maxValue:
        maxValue = values[i]

    self.countingSort(values, minValue, maxValue)


  def countingSort(self, ar, minVal, maxVal):
    """
    Sorts values in the range of [minVal, maxVal] in O(n+maxVal-maxVal)
    """
    sz = maxVal - minVal + 1
    b = [0]*sz
    for i in range(0, len(ar)):
      b[ar[i] - minVal] += 1
    k = 0
    for i in range(0, sz):
      while b[i] > 0:
        b[i] -= 1
        ar[k] = i + minVal
        k += 1



if __name__ == '__main__':
  """
  Example usage
  """
  sorter = CountingSort()
  nums = [+4, -10, +0, +6, +1, -5, -5, +1, +1, -2, 0, +6, +8, -7, +10]
  sorter.sort(nums)

  # Prints:
  # [-10, -7, -5, -5, -2, 0, 0, 1, 1, 1, 4, 6, 6, 8, 10]
  print(nums)
