'''
 * @file   IntStack.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   23 Jun 2020
 * @version 0.1
 * @brief   An integer implementation of a stack.
 * This file contains an implementation of an integer only stack which is extremely quick and
 * lightweight.
'''

import time
from collections import deque
from queue import LifoQueue
from ListStack import ListStack
from ArrayStack import ArrayStack
from array import array as arr
from Stack import Stack


class IntStack(Stack):
  ''' 
  An integer implementation of a stack
  '''
  def __init__(self, maxSize):
    '''
    maxSize is the maximum number of items
    that can be in the queue at any given time
    ''' 
    self.pos = 0
    self.ar = arr('i', (0 for i in range(maxSize)))


  def size(self):
    """
    Returns the number of elements insize the stack
    """
    return self.pos


  def isEmpty(self):
    """
    Returns true/false on whether the stack is empty
    """
    return self.pos == 0


  def peek(self):
    if self.isEmpty():
      raise Exception('Empty Stack')
    return self.ar[self.pos - 1]


  def push(self, value):
    """
    Add an element to the top of the stack
    """
    self.ar[self.pos] = value
    self.pos += 1


  def pop(self):
    """
    Make sure you check that the stack is not empty before calling pop!
    """
    if self.isEmpty():
      raise Exception('Empty Stack')
    self.pos -= 1
    return self.ar[self.pos]


def benchMarkTest():
  """
  BenchMark IntStack vs Python deque.
  """
  n = 10000000
  intStack = IntStack(n)


  # Implemenation using IntStack module (5.046 sec)
  start = time.process_time()
  for i in range(0, n):
    intStack.push(i)
  for i in range(0, n):
    intStack.pop()
  end = time.process_time()    
  print("IntStack Time: ", (end - start))



  # Implemenation using ListStack module (29.609375 sec)
  listStack = ListStack()
  start = time.process_time()
  for i in range(0, n):
    listStack.push(i)
  for i in range(0, n):
    listStack.pop()
  end = time.process_time()
  print("ListStack Time: ", (end - start))




  # Implemenation using ArrayStack module (7.09375 sec)
  arrayStack = ArrayStack(0)
  start = time.process_time()
  for i in range(0, n):
    arrayStack.push(i)
  for i in range(0, n):
    arrayStack.pop()
  end = time.process_time()
  print("ArrayStack Time: ", (end - start))



  # Implementation using collections.deque (1.28125 sec)
  # Python stack can be implemented using deque class from collections module. 
  # Deque is preferred over list in the cases where we need quicker append and 
  # pop operations from both the ends of the container, as deque provides an O(1) 
  # time complexity for append and pop operations as compared to list which 
  # provides O(n) time complexity.
  # Same methods on deque as seen in list are used, append() and pop().
  stackDeque = deque()    
  # deque is slower when you give it an initial capacity.
  start = time.process_time()
  for i in range(0, n):
    stackDeque.append(i)
  for i in range(0, n):
    stackDeque.pop()
  end = time.process_time()
  print("DequeStack Time: ", (end - start))



  # Implemenation using queue module (33.765625 sec)
  # Queue module also has a LIFO Queue, which is basically a Stack. Data is 
  # inserted into Queue using put() function and get() takes data out from the Queue.
  lifoStack = LifoQueue(maxsize = n) 
  start = time.process_time()
  for i in range(0, n):
    lifoStack.put(i)
  for i in range(0, n):
    lifoStack.get()
  end = time.process_time()
  print("LIFOStack Time: ", (end - start))



if __name__ == '__main__':
  """
  Example usage
  """

  s = IntStack(5)

  s.push(1)
  s.push(2)
  s.push(3)
  s.push(4)
  s.push(5)

  print(s.pop()) # 5
  print(s.pop()) # 4
  print(s.pop()) # 3

  s.push(3)
  s.push(4)
  s.push(5)

  while s.isEmpty() is False:
    print(s.pop())

  benchMarkTest()
