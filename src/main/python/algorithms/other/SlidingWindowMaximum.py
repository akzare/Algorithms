'''
 * @file   SlidingWindowMaximum.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   30 Jun 2020
 * @version 0.1
 * @brief   SlidingWindowMaximum implementation
 * This file contain an implementation of the maximum sliding window problem. This code has been
 * tested against the judge data on:
 *
 * <p>https://leetcode.com/problems/sliding-window-maximum/description/
'''

import math
from collections import deque

class SlidingWindowMaximum():

  def __init__(self, values):
    if values == None:
      raise Exception()
    self.values = values
    self.N = len(values)
    self.lo = 0
    self.hi = 0
    self.deque = deque()


  def advance(self):
    """
    Advances the front of the window by one unit    
    """

    # Remove all the worse values in the back of the deque
    while len(self.deque) and self.values[self.deque[-1]] < self.values[self.hi]:
      self.deque.pop() # Change the '<' sign here ^^^ to '>' for minimum sliding window

    # Add the next index to the back of the deque
    self.deque.append(self.hi)

    # Increase the window size
    self.hi += 1


  def shrink(self):
    """
    Retracks the back of the window by one unit
    """

    # Decrease window size by pushing it forward
    self.lo += 1

    # Remove elements in the front of the queue whom are no longer
    # valid in the reduced window.
    while len(self.deque) and self.deque[0] < self.lo: 
      self.deque.popleft()


  # Query the current maximum value in the window
  def getMax(self):
    if self.lo >= self.hi: 
      raise Exception("Make sure lo < hi")
#    print(self.deque)
    if len(self.deque):
      return self.values[self.deque[0]]
    else:
      return None

