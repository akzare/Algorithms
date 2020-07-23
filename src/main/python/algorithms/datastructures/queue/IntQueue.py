'''
 * @file   IntQueue.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         liujingkun, liujkon@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   23 Jun 2020
 * @version 0.1
 * @brief   This file contains an implementation of an integer only queue.
 *  
'''

import time
from array import array as arr
from collections import deque
from Queue import Queue


class IntQueue(Queue):
  ''' 
  An integer only implementation of a queue
  '''
  def __init__(self, maxSize):
    """
    maxSize is the maximum number of items
    that can be in the queue at any given time
    """ 
    self.front = 0
    self.end = 0
    self.qSize = 0
    self.data = arr('i', (0 for i in range(maxSize)))


  def isEmpty(self):
    """
    Return true/false on whether the queue is empty
    """
    return self.qSize == 0


  def size(self):
    """
    Return the number of elements inside the queue
    """  
    return self.qSize


  def peek(self):
    if self.isEmpty():
      raise Exception('Queue is empty')
      
    self.front = self.front % len(self.data)
    return self.data[self.front]


  def isFull(self):
    return self.qSize == len(self.data)


  def offer(self, value):
    """
    Add an element to the queue
    """
    if self.isFull():
      raise Exception("Queue too small!")
    
    self.data[self.end] = value
    self.end += 1
    self.qSize += 1
    self.end = self.end % len(self.data)


  def poll(self):
    """
    Make sure you check is the queue is not empty before calling poll!
    """
    if self.isEmpty():
      raise Exception('Queue is empty')
    
    self.qSize -= 1
    self.front = self.front % len(self.data)
    d = self.data[self.front]
    self.front += 1
    return d



def benchMarkTest():
  """
  BenchMark IntQueue vs ArrayDeque.
  """  

  n = 10000000
  intQ = IntQueue(n)

  # IntQueue times at around 12.109375 seconds
  start = time.process_time()
  for i in range(0, n):
    intQ.offer(i)
  for i in range(0, n):
    intQ.poll()
  end = time.process_time()
  print("IntQueue Time: ", (end - start))

  # ArrayDeque times at around 1.1875 seconds
  arrayDeque = deque()
  start = time.process_time()
  for i in range(0, n):
    arrayDeque.append(i)
  for i in range(0, n):
    arrayDeque.popleft()
  end = time.process_time()
  print("ArrayDeque Time: ", (end - start))



if __name__ == '__main__':
  """
  Example usage
  """

  q = IntQueue(5)

  q.offer(1)
  q.offer(2)
  q.offer(3)
  q.offer(4)
  q.offer(5)

  print(q.poll()) # 1
  print(q.poll()) # 2
  print(q.poll()) # 3
  print(q.poll()) # 4

  print(q.isEmpty()) # false

  q.offer(1);
  q.offer(2);
  q.offer(3);

  print(q.poll()) # 5
  print(q.poll()) # 1
  print(q.poll()) # 2
  print(q.poll()) # 3

  print(q.isEmpty()) # true

  benchMarkTest()
