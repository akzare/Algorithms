'''
 * @file   InterpolationSearch.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   An implementation of interpolation search
'''

import math

class InterpolationSearch():
  """
  A fast alternative to a binary search when the elements are uniformly distributed. This
  algorithm runs in a time complexity of ~O(log(log(n))).  
  """
  def __init__(self):
    pass

  def interpolationSearch(self, nums, val):
    """
    @param nums - an ordered list containing uniformly distributed values.
    @param val - the value we're looking for in 'nums'
    """
    lo = 0
    mid = 0
    hi = len(nums) - 1
    
    while nums[lo] <= val and nums[hi] >= val:
      mid = lo + ((val - nums[lo]) * (hi - lo)) // (nums[hi] - nums[lo])
      if nums[mid] < val:
        lo = mid + 1
      elif nums[mid] > val:
        hi = mid - 1
      else:
        return mid

    if nums[lo] == val:
      return lo
    return -1


if __name__ == '__main__':
  """
  Example usage
  """
  s = InterpolationSearch()
    
  values = [10, 20, 25, 35, 50, 70, 85, 100, 110, 120, 125]

  # Since 25 exists in the values array the interpolation search
  # returns that it has found 25 at the index 2
  print(s.interpolationSearch(values, 25))

  # 111 does not exist so we get -1 as an index value
  print(s.interpolationSearch(values, 111))
