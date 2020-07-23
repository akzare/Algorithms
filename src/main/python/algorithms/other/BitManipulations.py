'''
 * @file   BitManipulations.py
 * @author (original JAVA) Micah Stairs
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   29 Jun 2020
 * @version 0.1
 * @brief   B
 * Fundamental bit manipulation operations you must know Time Complexity: O(1)
'''

class BitManipulations():

  def __init__(self):
    pass


  def setBit(self, set, i):
    """
    Sets the i'th bit to 1
    """
    return set | (1 << i)


  def isSet(self, set, i):
    """
    Checks if the i'th is set
    """
    return (set & (1 << i)) != 0


  def clearBit(self, set, i):
    """
    Sets the i'th bit to zero
    """
    return set & ~(1 << i)


  def toggleBit(self, set, i):
    """
    Toggles the i'th bit from 0 -> 1 or 1 -> 0
    """
    return set ^ (1 << i)


  def setAll(self, n):
    """
    Returns a number with the first n bits set to 1
    """
    return (1 << n) - 1


  def isPowerOfTwo(self, n):
    """
    Verifies if a number n is a power of two
    """
    return n > 0 and (n & (n - 1)) == 0
