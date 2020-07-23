'''
 * @file   LinkedQueue.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   23 Jun 2020
 * @version 0.1
 * @brief   A simple queue implementation with a linkedlist.
'''

from Queue import Queue
from DoublyLinkedList import DoublyLinkedList

class LinkedQueue(Queue):
  ''' 
  A linked list implementation of a queue
  '''
  def __init__(self): 
    self.list = DoublyLinkedList()
    self.iterList = iter(self.list)


  def size(self):
    """
    Return the size of the queue
    """
    return self.list.size()


  def isEmpty(self):
    """
    Returns whether or not the queue is empty
    """
    return self.size() == 0


  def peek(self):
    """
    Peek the element at the front of the queue
    The method throws an error is the queue is empty
    """
    if self.isEmpty():
      raise Exception('Queue Empty')
    return self.list.peekFirst()


  def poll(self):
    """
    Poll an element from the front of the queue
    The method throws an error is the queue is empty
    """
    if self.isEmpty():
      raise Exception('Queue Empty')
    return self.list.removeFirst()


  def offer(self, elem):
    """
    Add an element to the back of the queue
    """
    self.list.addLast(elem)


  def __iter__(self): 
    """
     Called when iteration is initialized

     Return an iterator to allow the user to traverse
     through the elements found inside the queue
    """
    self.iterList = iter(self.list)
    return self


  def __next__(self): 
    """
    To move to next element. 
    """  
    return next(self.iterList)


if __name__ == '__main__':
  q = LinkedQueue()

  q.offer(1);
  q.offer(2);
  q.offer(3);
  q.offer(4);
  q.offer(5);

  print(q.poll()) # 1
  print(q.poll()) # 2
  print(q.poll()) # 3
  print(q.poll()) # 4

  print(q.isEmpty()) # false

  q.offer(1)
  q.offer(2)
  q.offer(3)

  print(q.poll()) # 5
  print(q.poll()) # 1
  print(q.poll()) # 2
  print(q.poll()) # 3

  print(q.isEmpty()) # true
