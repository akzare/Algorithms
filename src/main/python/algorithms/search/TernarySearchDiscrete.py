'''
 * @file   TernarySearchDiscrete.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   An implementation of Ternary search
 * Ternary search is similar to binary search except that it works on a function which decreases and
 * then increases. This implementation of ternary search works on discrete values and returns the
 * input value corresponding with the minimum output value of the function you're searching on.
 *
 * <p>Time Complexity: O(log(high - low)).
 *
 * <p>NOTE: You can also work with a function which increases and then decreases, simply negate your
 * function :)
'''

import math

# A discrete function is just a set of data points.
function = [16, 12, 10, 3, 6, 7, 9, 10, 11, 12, 13, 17]


# Define your own function on whatever you're attempting to ternary
# search. Remember that your function must be a discrete and a unimodal
# function, this means a function which decreases then increases (U shape)
f = lambda i: function[i]


class TernarySearchDiscrete():
  """
  """
  def __init__(self):
    # Define a very small epsilon value to compare double values.
    self.EPS = 0.000000001


  def discreteTernarySearch(self, lo, hi):
    while lo != hi:
      if hi - lo == 1:
        return min(f(lo), f(hi))
      if hi - lo == 2:
        return min(f(lo), min(f(lo + 1), f(hi)))
    
      mid1 = (2 * lo + hi) // 3
      mid2 = (lo + 2 * hi) // 3
      res1 = f(mid1)
      res2 = f(mid2)
      if abs(res1 - res2) < 0.000000001:
        lo = mid1
        hi = mid2
      elif res1 > res2:
        lo = mid1
      else:
        hi = mid2

    return lo



if __name__ == '__main__':
  """
  Example usage
  """
  ts = TernarySearchDiscrete()
  
  lo = 0
  hi = len(function) - 1

  # Use ternary search to find the minimum value on the
  # whole interval of out function.
  minValue = ts.discreteTernarySearch(lo, hi)
  print('{:.4f}\n'.format(minValue))
