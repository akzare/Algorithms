'''
 * @file   RadixSort.py
 * @author (original JAVA) EAlexa and William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   Radix sort implementation
 * See https://en.wikipedia.org/wiki/Radix_sort for details on runtime and complexity Radix sorts
 * operates in O(nw) time, where n is the number of keys, and w is the key length where w is
 * constant on primitive types like Integer which gives it a better performance than other
 * compare-based sort algorithms, like i.e. QuickSort
'''

import math 

class RadixSort():
  """
  Mergesort implements InplaceSort for ease of testings, but in reality
  it is not really a good fit for an inplace sorting algorithm.
  """
  def __init__(self):
    pass


  def sort(self, values):
    if values == None: 
      return
    return self.radixSort(values)


  def getMax(self, array):
    maxNum = array[0]
    for i in range(0, len(array)):
      if array[i] > maxNum:
        maxNum = array[i]

    return maxNum


  def calculateNumberOfDigits(self, number):
    return int(math.log(number, 10) + 1)


  def radixSort(self, numbers):
    """
    Requires all numbers to be greater than or equal to 1
    """
    if numbers == None or len(numbers) <= 1:
      return

    maximum = self.getMax(numbers)
    numberOfDigits = self.calculateNumberOfDigits(maximum)
    placeValue = 1
    while numberOfDigits > 0:
      numberOfDigits -= 1
      numbers = self.countSort(numbers, placeValue)
      placeValue *= 10
      
    return numbers


  def countSort(self, numbers, placeValue):
    rangeParm = 10

    frequency = [0]*rangeParm
    sortedValues = [None]*len(numbers)

    for i in range(0, len(numbers)):
      digit = (numbers[i] // placeValue) % rangeParm
      frequency[digit] += 1


    for i in range(1, rangeParm):
      frequency[i] += frequency[i - 1]


    for i in range(len(numbers) - 1, -1, -1):
      digit = (numbers[i] // placeValue) % rangeParm
      sortedValues[frequency[digit] - 1] = numbers[i]
      frequency[digit] -= 1

    return sortedValues[:len(numbers)]



if __name__ == '__main__':
  """
  Example usage
  """
  sorter = RadixSort()
  numbers = [387, 468, 134, 123, 68, 221, 769, 37, 7, 890, 1, 587]
  numbers = sorter.sort(numbers)
  # Prints:
  # [1, 7, 37, 68, 123, 134, 221, 387, 468, 587, 769, 890]
  print(numbers)
