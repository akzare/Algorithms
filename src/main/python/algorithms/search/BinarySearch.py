'''
 * @file   BinarySearch.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   BinarySearch implementation
'''

import math

class BinarySearch():

  def __init__(self):
    # Comparing double values directly is bad practice.
    # Using a small epsilon value is the preferred approach
    self.EPS = 0.00000001

  def binarySearch(self, lo, hi, target, function):

    if hi <= lo:
      raise Exception("hi should be greater than lo")

    mid = 0
    while True:

      # Find the middle point
      mid = (hi + lo) / 2.0

      # Compute the value of our function for the middle point
      # Note that f can be any function not just the square root function
      value = function(mid)

      if value > target:
        hi = mid
      else:
        lo = mid

      if (hi - lo) > self.EPS:
        break

    return mid


# ToDo: The validity of the implementation must be checked!
if __name__ == '__main__':
  """
  Example usage
  """
  bs = BinarySearch()

  # EXAMPLE #1
  # Suppose we want to know what the square root of 875 is and
  # we have no knowledge of the wonderful Math.sqrt() function.
  # One approach is to use a binary search because we know that
  # the square root of 875 is bounded in the region: [0, 875].
  #
  # We can define our function to be f(x) = x*x and our target
  # value to be 875. As we binary search on f(x) approaching
  # successively closer values of 875 we get better and better
  # values of x (the square root of 875)

  lo = 0.0
  hi = 875.0
  target = 875.0
  sqr_fun = lambda x: x * x

  sqrtVal = bs.binarySearch(lo, hi, target, sqr_fun)
  print('sqrt({:.2f}) = {:.5f}, x^2 = {:.5f}\n'.format(target, sqrtVal, (sqrtVal * sqrtVal)))

  # EXAMPLE #2
  # Suppose we want to find the radius of a sphere with volume 100m^3 using
  # a binary search. We know that for a sphere the volume is given by
  # V = (4/3)*pi*r^3, so all we have to do is binary search on the radius.
  #
  # Note: this is a silly example because you could just solve for r, but it
  # shows how binary search can be a powerful technique.

  radiusLowerBound = 0
  radiusUpperBound = 1000
  volume = 100.0
  sphereVolumeFunction = lambda r: (4.0 / 3.0) * math.pi * r * r * r

  sphereRadius = bs.binarySearch(radiusLowerBound, radiusUpperBound, volume, sphereVolumeFunction)

  print('Sphere radius = {:.5f}\n'.format(sphereRadius))
