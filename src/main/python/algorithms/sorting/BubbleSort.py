'''
 * @file   BubbleSort.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   27 Jun 2020
 * @version 0.1
 * @brief   Bubble sort implementation
'''


class BubbleSort():

  def __init__(self):
    pass


  def sort(self, ar):
    """
    Sort the array using bubble sort. The idea behind
    bubble sort is to look for adjacent indexes which
    are out of place and interchange their elements
    until the entire array is sorted.
    """
    if ar == None:
      return

    sorted = False
    while True:
      sorted = True
      for i in range(1, len(ar)):
        if ar[i] < ar[i - 1]:
          self.swap(ar, i - 1, i)
          sorted = False
      if sorted:
        break


  def swap(self, ar, i, j):
    tmp = ar[i]
    ar[i] = ar[j]
    ar[j] = tmp


if __name__ == '__main__':
  """
  Example usage
  """
  array = [10, 4, 6, 8, 13, 2, 3]
  sorter = BubbleSort()
  sorter.sort(array)
  # Prints:
  # [2, 3, 4, 6, 8, 10, 13]
  print(array)
