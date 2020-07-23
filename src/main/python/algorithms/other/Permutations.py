'''
 * @file   Permutations.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   Permutations implementation
 * Here we present two methods (recursive and iterative) of generating all the permutations of a
 * list of elements.
 *
 * <p>Time Complexity: O(n!)
'''

import math

class Permutations():

  def __init__(self):
    pass

  ############################################################
  # RECURSIVE APPROACH 

  def generatePermutations(self, sequence):
    """
    Generates all the permutations of a sequence of objects
    """
    if sequence == None:
      return
    used = [False]*len(sequence)
    picked = [0]*len(sequence)
    self.permutations(0, used, picked, sequence)


  def permutations(self, at, used, picked, sequence):
    """
    Recursive method to generate all the permutations of a sequence
    at       -> Current element we're considering
    used     -> The elements we have currently selected in our permutation
    picked   -> The order of the indexes we have selected in our permutation
    sequence -> The array we're generating permutations for
    """

    N = len(sequence)

    # We reached the end, so we've found a valid permutation!
    if at == N:

      # Print permutation
      print("[ ", end = '')
      for i in range(0, N):
        print('{} '.format(sequence[picked[i]]), end = '')
      print("]")

    else:

      for i in range(0, N):

        # We can only select elements once, so make sure we do
        # not select an element which has already been chosen
        if not used[i]:

          # Select this element and track in picked which
          # element was chosen for this permutations
          used[i] = True
          picked[at] = i
          self.permutations(at + 1, used, picked, sequence)

          # Backtrack (unselect element)
          used[i] = False



  ############################################################
  # ITERATIVE APPROACH

  def nextPermutation(self, sequence):
    """
    Generates the next ordered permutation in-place (skips repeated permutations).
    Calling this when the array is already at the highest permutation returns false.
    Recommended usage is to start with the smallest permutations and use a do while
    loop to generate each successive permutations (see main for example).    
    """
    first = self.getFirst(sequence)
    if first == -1: 
      return False
    toSwap = len(sequence) - 1
    while sequence[first] >= sequence[toSwap]: 
      toSwap -= 1
    self.swap(sequence, first, toSwap)
    first += 1
    toSwap = len(sequence) - 1
    while first < toSwap:
      self.swap(sequence, first, toSwap)
      first += 1
      toSwap -= 1
    return True


  def getFirst(self, sequence):
    for  i in range(len(sequence) - 2, -1, -1):
      if sequence[i] < sequence[i + 1]:
        return i
    return -1


  def swap(self, sequence, i, j):
    tmp = sequence[i]
    sequence[i] = sequence[j]
    sequence[j] = tmp


if __name__ == '__main__':
  """
  Example usage
  """
  p = Permutations()
  
  sequence = [1, 1, 2, 3]
  p.generatePermutations(sequence)
  # prints:
  # [ 1 1 2 3 ]
  # [ 1 1 3 2 ]
  # [ 1 2 1 3 ]
  # [ 1 2 3 1 ]
  # [ 1 3 1 2 ]
  # [ 1 3 2 1 ]
  # [ 1 1 2 3 ]
  # [ 1 1 3 2 ]
  # [ 1 2 1 3 ]
  # [ 1 2 3 1 ]
  # [ 1 3 1 2 ]
  # [ 1 3 2 1 ]
  # [ 2 1 1 3 ]
  # [ 2 1 3 1 ]
  # [ 2 1 1 3 ]
  # [ 2 1 3 1 ]
  # [ 2 3 1 1 ]
  # [ 2 3 1 1 ]
  # [ 3 1 1 2 ]
  # [ 3 1 2 1 ]
  # [ 3 1 1 2 ]
  # [ 3 1 2 1 ]
  # [ 3 2 1 1 ]
  # [ 3 2 1 1 ]


  alpha = ["A", "B", "C", "D"]
  while True:

    print(str(alpha))

    # Loop while alpha is not at its highest permutation ordering
    if not p.nextPermutation(alpha):
      break
  
  # prints:
  # [A, B, C, D]
  # [A, B, D, C]
  # [A, C, B, D]
  # [A, C, D, B]
  # [A, D, B, C]
  # [A, D, C, B]
  # [B, A, C, D]
  # [B, A, D, C]
  # [B, C, A, D]
  # [B, C, D, A]
  # [B, D, A, C]
  # [B, D, C, A]
  # [C, A, B, D]
  # [C, A, D, B]
  # [C, B, A, D]
  # [C, B, D, A]
  # [C, D, A, B]
  # [C, D, B, A]
  # [D, A, B, C]
  # [D, A, C, B]
  # [D, B, A, C]
  # [D, B, C, A]
  # [D, C, A, B]
  # [D, C, B, A]
