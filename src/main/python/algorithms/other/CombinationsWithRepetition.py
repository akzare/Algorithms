'''
 * @file   CombinationsWithRepetition.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   Combinations implementation
 * Here I show how you can generate all the combinations of a sequence of size r which are repeated
 * at most k times.
 *
 * <p>Time Complexity: O(n+r-1 choose r) = O((n+r-1)!/(r!(n-1)!))
'''

import math

class CombinationsWithRepetition():

  def __init__(self):
    pass


  def combinationsWithRepetition(self, sequence, usedCount, at, r, k):
    """
   * Computes all combinations of elements of 'r' elements which can be repeated at most 'k' times
   * each.
   *
   * @param sequence - The sequence containing all the elements we wish to take combinations from
   * @param usedCount - Tracks how many of each element we currently have selected
   * @param at - The current position we're at in the sequence
   * @param r - The number of elements we're choosing
   * @param k - The maximum number of times each element is allowed to be picked
    """

    N = len(sequence)

    # We reached the end
    if at == N:

      # We selected 'r' elements in total
      if r == 0:

        # Print combination
        print("{ ", end = '')
        for i in range(0, N):
          for j in range(0, usedCount[i]):
            print('{} '.format(sequence[i]), end = '')
        print("}")


    else:

      # For this particular time at position 'at' try including it each of [0, k] times
      for itemCount in range(0, k+1):

        # Try including this element itemCount number of times (this is possibly more than once)
        usedCount[at] = itemCount

        self.combinationsWithRepetition(sequence, usedCount, at + 1, r - itemCount, k)



  def printCombinationsWithRepetition(self, sequence, r, k):
    """
    Given a sequence this method prints all the combinations of size
    'r' in a given sequence which has each element repeated at most 'k' times
    """
    if sequence == None: 
      return
    n = len(sequence)
    if r > n: 
      raise Exception("r must be <= n")
    if k > r: 
      raise Exception("k must be <= r")

    usedCount = [0]*len(sequence)
    self.combinationsWithRepetition(sequence, usedCount, 0, r, k)


if __name__ == '__main__':
  """
  Example usage
  """

  cwr = CombinationsWithRepetition()
  # Prints all combinations of size 3 where
  # each element is repeated at most twice
  seq = [1, 2, 3, 4]
  cwr.printCombinationsWithRepetition(seq, 3, 2)
  # prints:
  # { 3 4 4 }
  # { 3 3 4 }
  # { 2 4 4 }
  # { 2 3 4 }
  # { 2 3 3 }
  # { 2 2 4 }
  # { 2 2 3 }
  # { 1 4 4 }
  # { 1 3 4 }
  # { 1 3 3 }
  # { 1 2 4 }
  # { 1 2 3 }
  # { 1 2 2 }
  # { 1 1 4 }
  # { 1 1 3 }
  # { 1 1 2 }
