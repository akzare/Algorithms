'''
 * @file   SelectionSort.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   Selection sort implementation
'''


class SelectionSort():
  """
  """
  def __init__(self):
    pass


  def sort(self, values):
    if values == None: 
      return
    self.selectionSort(values)


  def selectionSort(self, array):
    N = len(array)

    for i in range(0, N):
      # Find the index beyond i with a lower value than i
      swapIndex = i
      for j in range(i + 1, N):
        if array[j] < array[swapIndex]:
          swapIndex = j

      self.swap(array, i, swapIndex)


  def swap(self, ar, i, j):
    tmp = ar[i]
    ar[i] = ar[j]
    ar[j] = tmp


if __name__ == '__main__':
  """
  Example usage
  """
  sorter = SelectionSort()
  array = [10, 4, 6, 8, 13, 2, 3]
  sorter.sort(array)
  # Prints:
  # [2, 3, 4, 6, 8, 10, 13]
  print(array)
