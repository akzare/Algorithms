'''
 * @file   ArrayStack.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *                         liujingkun, liujkon@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   22 Jun 2020
 * @version 0.1
 * @brief   An array implementation of a queue.
'''

from Queue import Queue

class ArrayQueue(Queue):
  ''' 
  An array implementation of a stack
  '''
  def __init__(self, obj, capacity): 
    self.qSize = 0
    self.data = [obj for i in range(capacity)]
    self.front = 0
    self.rear = 0


  def size(self):
    return self.adjustIndex(self.rear + len(self.data) - self.front, len(self.data))


  def offer(self, elem):
    if self.isFull():
      raise Exception('Queue is full')

    self.data[self.rear] = elem
    self.rear += 1
    self.rear = self.adjustIndex(self.rear, len(self.data))


  def poll(self):
    if self.isEmpty():
      raise Exception('Queue is empty')
    self.front = self.adjustIndex(self.front, len(self.data))
    d = self.data[self.front]
    self.front += 1
    return d


  def peek(self):
    if self.isEmpty():
      raise Exception('Queue is empty')
    self.front = self.adjustIndex(self.front, len(self.data))
    return self.data[self.front]


  def isEmpty(self):
    return self.rear == self.front


  def isFull(self):
    return (self.front + len(self.data) - self.rear) % len(self.data) == 1


  def adjustIndex(self, index, size):
    return index - size if index >= size else index


if __name__ == '__main__':
  q = ArrayQueue(0, 6)

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
