'''
 * @file   PowerSet.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   30 Jun 2020
 * @version 0.1
 * @brief   PowerSet implementation
 * This code snippet shows how to generate the powerset of a set which is the set of all subsets of
 * a set. There are two common ways of doing this which are to use the binary representation of
 * numbers on a computer or to do it recursively. Both methods are shown here, pick your flavor!
 *
 * <p>Time Complexity: O( 2^n )
'''

import math

class PowerSet():

  def __init__(self):
    pass


  def powerSetUsingBinary(self, set):
    """
    Use the fact that numbers represented in binary can be
    used to generate all the subsets of an array    
    """

    N = len(set)
    MAX_VAL = 1 << N

    for subset in range(0, MAX_VAL):
      print("{ ", end = '')
      for i in range(0, N):
        mask = 1 << i
        if (subset & mask) == mask: 
          print('{} '.format(set[i]), end = '')

      print("}")



  def powerSetRecursive(self, at, set, used):
    """
    Recursively generate the powerset (set of all subsets) of an array by maintaining
    a boolean array used to indicate which element have been selected
    """

    if at == len(set):

      # Print found subset!
      print("{ ", end = '')
      for i in range(0, len(set)):
        if used[i]:
          print('{} '.format(set[i]), end = '')
      print("}");

    else:

      # Include this element
      used[at] = True
      self.powerSetRecursive(at + 1, set, used)

      # Backtrack and don't include this element
      used[at] = False
      self.powerSetRecursive(at + 1, set, used)



if __name__ == '__main__':
  """
  Example usage
  """
  ps = PowerSet()

  # Example usage:
  set = [1, 2, 3]

  ps.powerSetUsingBinary(set)
  # prints:
  # { }
  # { 1 }
  # { 2 }
  # { 1 2 }
  # { 3 }
  # { 1 3 }
  # { 2 3 }
  # { 1 2 3 }

  print()

  ps.powerSetRecursive(0, set, [False]*len(set))
  # prints:
  # { 1 2 3 }
  # { 1 2 }
  # { 1 3 }
  # { 1 }
  # { 2 3 }
  # { 2 }
  # { 3 }
  # { }
