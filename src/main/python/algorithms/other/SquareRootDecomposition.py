'''
 * @file   SquareRootDecomposition.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   30 Jun 2020
 * @version 0.1
 * @brief   SquareRootDecomposition implementation
 * Range queries in O(sqrt(n)) and point updates in O(1). Currently this implementation supports
 * summing over the entries in the array, but it can be modified to support many different
 * operations.
 *
 * <p>Time Complexity: Point update in O(1) and query in O(sqrt(n))
'''

import math

class SquareRootDecomposition():

  def __init__(self, values):
    """
    Creates an empty range [0,n]
    """
    sz = len(values)
    self.blockSize = int(math.sqrt(sz))
    self.nBlocks = (sz // self.blockSize) + 1
    self.blocks = [0]*self.nBlocks
    self.arr = [0]*sz

    for i in range(0, sz):
      self.set(i, values[i])



  def blockID(self, index):
    return index // self.blockSize



  def set(self, index, val):
    """
    Sets [index, index] = val
    """
    self.blocks[self.blockID(index)] -= self.arr[index];
    self.blocks[self.blockID(index)] += val
    self.arr[index] = val



  def query(self, lo, hi):
    """
    Get sum query from [lo, hi] in O(sqrt(n))
    """

    sum = 0
    loId = self.blockID(lo)
    hiId = self.blockID(hi)
    for i in range(loId + 1, hiId):
      sum += self.blocks[i]

    if loId == hiId:
      for i in range(lo, hi+1):
        sum += self.arr[i]
      return sum

    loMax = (((lo // self.blockSize) + 1) * self.blockSize) - 1
    hiMin = (hi // self.blockSize) * self.blockSize
    for i in range(lo, loMax+1):
      sum += self.arr[i]
    for i in range(hiMin, hi+1):
      sum += self.arr[i]

    return sum



if __name__ == '__main__':
  """
  Square root decomposition range query example usage
  """

  values = [1, 2, 3, 4, 5, 6, 7, 8, 9]
  rng = SquareRootDecomposition(values)

  # Prints: The sum from [0,8] is: 45
  print('The sum from [{},{}] is: {}\n'.format(0, 8, rng.query(0, 8)))

  # Prints: The sum from [2,2] is: 3
  print('The sum from [{},{}] is: {}\n'.format(2, 2, rng.query(2, 2)))

  # Prints: The sum from [3,4] is: 9
  print('The sum from [{},{}] is: {}\n'.format(3, 4, rng.query(3, 4)))

  # Prints: The sum from [1,6] is: 27
  print('The sum from [{},{}] is: {}\n'.format(1, 6, rng.query(1, 6)))
