'''
 * @file   ListStack.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   22 Jun 2020
 * @version 0.1
 * @brief   A linked list implementation of a stack.
'''

from Stack import Stack
from DoublyLinkedList import DoublyLinkedList

class ListStack(Stack):
  ''' 
  A linked list implementation of a stack
  '''
  def __init__(self): 
    self.list = DoublyLinkedList()
    self.iterList = iter(self.list)


  def size(self):
    '''
    Return the number of elements in the stack    
    ''' 
    return self.list.size()


  def isEmpty(self):
    """
    Check if the stack is empty
    """
    return self.size() == 0


  def push(self, elem):
    """
    Push an element on the stack
    """
    self.list.addLast(elem)


  def pop(self):
    """
    Pop an element off the stack
    Throws an error is the stack is empty
    """
    if self.isEmpty():
      raise Exception('Empty Stack')
    return self.list.removeLast()


  def peek(self):
    """
    Peek the top of the stack without removing an element
    Throws an exception if the stack is empty
    """
    if self.isEmpty():
      raise Exception('Empty Stack')
    return self.list.peekLast()


  def __iter__(self): 
    """
     Called when iteration is initialized
    """
    self.iterList = iter(self.list)
    return self


  def __next__(self): 
    """
    To move to next element. 
    """  
    return next(self.iterList)
