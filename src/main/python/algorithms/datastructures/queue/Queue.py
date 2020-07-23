'''
 * @file   Queue.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *                         liujingkun, liujkon@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   23 Jun 2020
 * @version 0.1
 * @brief   An abstract base class for queue.
'''

from abc import ABC,abstractmethod 


class Queue(ABC):

  @abstractmethod
  def offer(self, elem):
    pass

  @abstractmethod
  def poll(self):
    pass

  @abstractmethod
  def peek(self):
    pass

  @abstractmethod
  def size(self):
    pass

  @abstractmethod
  def isEmpty(self):
    pass
