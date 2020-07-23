'''
 * @file   Combinations.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   Combinations implementation
 * Here we present two methods (recursive and iterative) of generating all the combinations of a set
 * by choosing only r of n elements.
 *
 * <p>Time Complexity: O( n choose r )
'''

import math

class Combinations():

  def __init__(self):
    pass

  def combinationsChooseR(self, set, r):
    """
    This method finds all the combinations of size r in a set
    """

    if r < 0:
      return
    if set == None:
      return

    used = [False]*len(set)
    self.combinations(set, r, 0, used)


  def combinations(self, set, r, at, used):
    """
    To find all the combinations of size r we need to recurse until we have
    selected r elements (aka r = 0), otherwise if r != 0 then we need to select
    an element which is found after the position of our last selected element
    """

    N = len(set)

    # Return early if there are more elements left to select than what is available.
    elementsLeftToPick = N - at
    if elementsLeftToPick < r:
      return

    # We selected 'r' elements so we found a valid subset!
    if r == 0:
      print("{ ", end = '')
      for i in range(0, N):
        if used[i]: 
          print('{} '.format(set[i]), end = '')
      print("}")

    else:

      for i in range(at, N):

        # Try including this element
        used[i] = True

        self.combinations(set, r - 1, i + 1, used)

        # Backtrack and try the instance where we did not include this element
        used[i] = False


  def nextCombination(self, selection, N, r):
    """
    Use this method in combination with a do while loop to generate all the combinations
    of a set choosing r elements in a iterative fashion. This method returns
    false once the last combination has been generated.
    NOTE: Originally the selection needs to be initialized to {0,1,2,3 ... r-1}    
    """
    if r > N:
      raise Exception("r must be <= N")
    i = r - 1
    while selection[i] == N - r + i:
      i -= 1
      if i < 0:
        return False
    selection[i] += 1
    for j in range(i + 1, r):
      selection[j] = selection[i] + j - i
    return True




if __name__ == '__main__':
  """
  Example usage
  """
  
  c = Combinations()

  # Recursive approach
  R = 3
  set = [1, 2, 3, 4, 5]
  c.combinationsChooseR(set, R)
  # prints:
  # { 1 2 3 }
  # { 1 2 4 }
  # { 1 2 5 }
  # { 1 3 4 }
  # { 1 3 5 }
  # { 1 4 5 }
  # { 2 3 4 }
  # { 2 3 5 }
  # { 2 4 5 }
  # { 3 4 5 }

  # Suppose we want to select all combinations of colors where R = 3
  colors = ["red", "purple", "green", "yellow", "blue", "pink"]
  R = 3

  # Initialize the selection to be {0, 1, ... , R-1}
  selection = [0, 1, 2]
  while True:

    # Print each combination
    for index in selection:
      print('{} '.format(colors[index]), end = '')
    print()

    if not c.nextCombination(selection, len(colors), R):
      break
  # prints:
  # red purple green
  # red purple yellow
  # red purple blue
  # red purple pink
  # red green yellow
  # red green blue
  # red green pink
  # red yellow blue
  # red yellow pink
  # red blue pink
  # purple green yellow
  # purple green blue
  # purple green pink
  # purple yellow blue
  # purple yellow pink
  # purple blue pink
  # green yellow blue
  # green yellow pink
  # green blue pink
  # yellow blue pink
