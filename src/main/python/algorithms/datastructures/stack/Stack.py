'''
 * @file   Stack.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   22 Jun 2020
 * @version 0.1
 * @brief   An abstract base class for stack.
'''

from abc import ABC,abstractmethod 


class Stack(ABC):

  @abstractmethod
  def size(self): 
    """
    return the number of elements in the stack
    """
    pass


  @abstractmethod
  def isEmpty(self):
    """
    return if the stack is empty
    """
    pass


  @abstractmethod
  def push(self, elem):
    """
    push the element on the stack
    """
    pass


  @abstractmethod
  def pop(self):
    """
    pop the element off the stack
    """
    pass


  @abstractmethod
  def peek(self):
    """
    """
    pass
