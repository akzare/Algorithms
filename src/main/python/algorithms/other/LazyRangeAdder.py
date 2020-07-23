'''
 * @file   LazyRangeAdder.py
 * @author (original JAVA) Atharva Thorve, aaathorve@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   30 Jun 2020
 * @version 0.1
 * @brief   LazyRangeAdder implementation
 * The LazyRangerAdder is a handy class for performing addition range updates of constant values on
 * an array. This range adder is especially useful for offline algorithms which know all range
 * updates ahead of time.
 *
 * <p>Time complexity to update O(1) but time complexity to finalize all additions is O(n)
'''

import math

class LazyRangeAdder():

  def __init__(self):

    # The number of elements in the input array.
    self.n = 0

    # The original input array
    self.array = []

    # The difference array with the deltas between values, size n+1
    self.differenceArray = []



  def lazyRangeAdder(self, array):
    """
    Initialize an instance of a LazyRangeAdder on some input values
    """
    self.array = array
    self.n = len(array)

    self.differenceArray = [0]*(self.n + 1)
    self.differenceArray[0] = self.array[0]
    for i in range(1, self.n):
      self.differenceArray[i] = self.array[i] - self.array[i - 1]



  def add(self, l, r, x):
    """
    Add `x` to the range [l, r] inclusive    
    """
    self.differenceArray[l] += x;
    self.differenceArray[r + 1] -= x;



  def done(self):
    """
    IMPORTANT: Make certain to call this method once all the additions
    have been made with add(l, r, x)
    """
    for i in range(0, self.n):
      if i == 0:
        self.array[i] = self.differenceArray[i]
      else:
        self.array[i] = self.differenceArray[i] + self.array[i - 1]




if __name__ == '__main__':
  """
  Example usage
  """
  la = LazyRangeAdder()
  
  # Array to be updated
  array = [10, 4, 6, 13, 8, 15, 17, 22]
  la.lazyRangeAdder(array)

  # After below add(l, r, x), the
  # elements should become [10, 14, 16, 23, 18, 15, 17, 22]
  la.add(1, 4, 10)
  la.done()
  print(array)

  # After below add(l, r, x), the
  # elements should become [22, 26, 28, 30, 25, 22, 24, 34]
  la.add(3, 6, -5)
  la.add(0, 7, 12)
  la.done()
  print(array)

