'''
 * @file   TernarySearch.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   An implementation of Ternary search
 * Ternary search is similar to binary search except that it works on a function which decreases and
 * then increases. This implementation of ternary search returns the input value corresponding with
 * the minimum output value of the function you're searching on.
'''

import math

class TernarySearch():
  """
  """
  def __init__(self):
    # Define a very small epsilon value to compare double values
    self.EPS = 0.000000001


  def ternarySearch(self, low, high, function):
    """
    Perform a ternary search on the interval low to high.
    Remember that your function must be a continuous unimodal
    function, this means a function which decreases then increases (U shape)
    """
    best = None
    while True:
      mid1 = (2 * low + high) // 3
      mid2 = (low + 2 * high) // 3
      res1 = function(mid1) 
      res2 = function(mid2)
      if res1 > res2:
        low = mid1
      else:
        high = mid2
      if best is not None and abs(best - mid1) < self.EPS:
        break
      best = mid1

    return best


if __name__ == '__main__':
  """
  Example usage
  """
  ts = TernarySearch()
  
  # Search for the lowest point on the function x^2 + 3x + 5
  # using a ternary search on the interval [-100, +100]
  function = lambda x: x * x + 3 * x + 5
  root = ts.ternarySearch(-100.0, +100.0, function)
  print('{:.4f}\n'.format(root))
