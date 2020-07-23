'''
 * @file   UniqueCombinations.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   30 Jun 2020
 * @version 0.1
 * @brief   UniqueCombinations implementation
 * This file shows you how to generate all the unique combinations of a set even though some
 * elements may be repeated. For example, if your set is {2, 2, 3, 3, 3} and you care only about
 * sets of size two (r = 2) then the unique sets are {{2,2}, {2,3}, {3,3}}.
 *
 * <p>Time Complexity: O( n choose r )
'''

import math

class UniqueCombinations():

  def __init__(self):
    pass
 
     
  def combinations(self, set, r):
    if set is None:
      return
    if r < 0:
      return

    # Sort the numbers so we can easily skip duplicates.
    set.sort()

    used = [False]*len(set)
    self.__combinations(0, r, used, set)


  def __combinations(self, at, r, used, set):

    n = len(set)

    # We select 'r' elements so we found a valid subset!
    if r == 0:

      subset = []
      for i in range(0, n):
        if used[i]:
          subset.append(set[i])
      print(subset)

    else:
      for i in range(at, n):

        # Since the elements are sorted we can skip duplicate
        # elements to ensure the uniqueness of our output.
        if i > at and set[i - 1] == set[i]:
          continue

        used[i] = True
        self.__combinations(i + 1, r - 1, used, set)
        used[i] = False



if __name__ == '__main__':
  """
  Example usage
  """
  uc = UniqueCombinations()

  # Example #1
  r = 2
  set = [2, 3, 3, 2, 3]
  uc.combinations(set, r)
  # Prints:
  # [2, 2]
  # [2, 3]
  # [3, 3]
  
  print()

  r = 3
  set = [1, 2, 2, 2, 3, 3, 4, 4]
  uc.combinations(set, r)
  # Prints:
  # [1, 2, 2]
  # [1, 2, 3]
  # [1, 2, 4]
  # [1, 3, 3]
  # [1, 3, 4]
  # [1, 4, 4]
  # [2, 2, 2]
  # [2, 2, 3]
  # [2, 2, 4]
  # [2, 3, 3]
  # [2, 3, 4]
  # [2, 4, 4]
  # [3, 3, 4]
  # [3, 4, 4]
