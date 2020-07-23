'''
 * @file   DoublyLinkedList.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   20 Jun 2020
 * @version 0.1
 * @brief   A doubly linked list implementation.
'''

import ctypes 


class Node(object):
  ''' 
  Internal node class to represent data
  '''
  def __init__(self, data, prev, next): 
    self.data = data
    self.prev = prev
    self.next = next


  def __repr__(self):
    return str(self.data)


class DoublyLinkedList(object): 
  ''' 
  DYNAMIC ARRAY CLASS (Similar to Python List) 
  '''
      
  def __init__(self): 
    self.llSize = 0 
    self.head = None
    self.tail = None
    self.travIter = None

  def __len__(self): 
    """ 
    Return number of elements sorted in array 
    """
    return self.llSize


  def clear(self):
    """ 
    Empty this linked list, O(n)
    """
    trav = self.head
    while trav is not None:
      next = trav.next
      trav.prev = trav.next = None
      trav.data = None
      trav = next

    self.head = None
    self.tail = None
    trav = None
    self.llSize = 0


  def size(self):
    """ 
    Return the size of this linked list
    """
    return self.llSize


  def isEmpty(self):
    """ 
    Is this linked list empty? 
    """
    return self.size() == 0


  def add(self, elem):
    """ 
    Add an element to the tail of the linked list, O(1)
    """
    self.addLast(elem)


  def addLast(self, elem):
    """ 
    Add a node to the tail of the linked list, O(1) 
    """
    if self.isEmpty():
      self.head = self.tail = Node(elem, None, None)
    else:
      self.tail.next = Node(elem, self.tail, None)
      self.tail = self.tail.next

    self.llSize += 1


  def addFirst(self, elem):
    """ 
    Add an element to the beginning of this linked list, O(1) 
    """
    if self.isEmpty():
      self.head = self.tail = Node(elem, None, None)
    else:
      self.head.prev = Node(elem, None, self.head)
      self.head = self.head.prev

    self.llSize += 1


  def addAt(self, index, data):
    """ 
    Add an element at a specified index
    """ 
    if index < 0:
      raise Exception('index should not be negative. The value of index was: {}'.format(index))
    
    if index == 0:
      self.addFirst(data)
      return

    if index == self.llSize:
      self.addLast(data)
      return

    temp = self.head
    for i in range(0, index - 1):
      temp = temp.next

    newNode = Node(data, temp, temp.next)
    temp.next.prev = newNode
    temp.next = newNode

    self.llSize += 1


  def peekFirst(self):
    """ 
    Check the value of the first node if it exists, O(1)
    """ 
    if self.isEmpty():
      raise Exception('Empty list')
    return self.head.data


  def peekLast(self):
    """ 
    Check the value of the last node if it exists, O(1)
    """ 
    if self.isEmpty():
      raise Exception('Empty list')
    return self.tail.data


  def removeFirst(self):
    """ 
    Remove the first value at the head of the linked list, O(1)
    """ 
    # Can't remove data from an empty list
    if self.isEmpty():
      raise Exception('Empty list')

    # Extract the data at the head and move
    # the head pointer forwards one node
    data = self.head.data
    self.head = self.head.next
    self.llSize -= 1

    # If the list is empty set the tail to null
    if self.isEmpty():
      self.tail = None

    # Do a memory cleanup of the previous node
    else:
      self.head.prev = None

    # Return the data that was at the first node we just removed
    return data


  def removeLast(self):
    """ 
    Remove the last value at the tail of the linked list, O(1)
    """ 
    # Can't remove data from an empty list
    if self.isEmpty():
      raise Exception('Empty list')

    # Extract the data at the tail and move
    # the tail pointer backwards one node
    data = self.tail.data
    self.tail = self.tail.prev
    self.llSize -= 1

    # If the list is now empty set the head to null
    if self.isEmpty():
      self.head = None

    # Do a memory clean of the node that was just removed
    else:
      self.tail.next = None

    # Return the data that was in the last node we just removed
    return data


  def __remove__(self, node):
    """ 
    Remove an arbitrary node from the linked list, O(1)
    """ 
    # If the node to remove is somewhere either at the
    # head or the tail handle those independently
    if node.prev == None:
      return self.removeFirst()
    if node.next == None:
      return self.removeLast()

    # Make the pointers of adjacent nodes skip over 'node'
    node.next.prev = node.prev;
    node.prev.next = node.next;

    # Temporarily store the data we want to return
    data = node.data

    # Memory cleanup
    node.data = None
    node.next = None
    node.prev = None
    node = None

    self.llSize -= 1

    # Return the data in the node we just removed
    return data


  def removeAt(self, index):
    """ 
    Remove a node at a particular index, O(n)
    """ 
    # Make sure the index provided is valid
    if index < 0 or index >= self.llSize:
      raise ValueError("wrong index")

    # Search from the front of the list
    if index < self.llSize / 2:
      i = 0
      trav = self.head
      while i != index:
        i += 1  
        trav = trav.next
      
    # Search from the back of the list
    else:
      i = self.llSize - 1
      trav = self.tail
      while i != index:
        i -= 1
        trav = trav.prev

    return self.__remove__(trav)


  def remove(self, obj):
    """ 
    Remove a particular value in the linked list, O(n)
    """ 
    trav = self.head

    # Support searching for null
    if obj is None:
      trav = self.head
      while trav is not None:
        if trav.data is None:
          self.__remove__(trav)
          return True

        trav = trav.next

    # Search for non null object
    else:
      trav = self.head

      while trav is not None:
        if obj == trav.data:
          self.__remove__(trav);
          return True
        
        trav = trav.next

    return False


  def indexOf(self, obj):
    """ 
    Find the index of a particular value in the linked list, O(n)
    """ 
    index = 0
    trav = self.head

    # Support searching for null
    if obj is None:
      while trav is not None:
        if trav.data is None:
          return index
        trav = trav.next
        index += 1
    # Search for non null object
    else:
      while trav is not None:
        if obj == trav.data:
          return index
        trav = trav.next
        index += 1      

    return -1


  def contains(self, obj):
    """ 
    Check if a value is contained within the linked list
    """ 
    return self.indexOf(obj) != -1


  def __iter__(self): 
    """
     Called when iteration is initialized
    """
    self.travIter = self.head
    return self


  def __next__(self): 
    """
    To move to next element. 
    """
    # Stop iteration if limit is reached 
    if self.travIter is None:
      raise StopIteration 
    
    # Store current travIter.data 
    data = self.travIter.data
    self.travIter = self.travIter.next
   
    # Else increment and return old value 
    return data


  def __repr__(self):
    sb = ""
    sb = sb + '[ '
    trav = self.head
    while trav is not None:
      sb = sb + str(trav.data)
      if trav.next is not None:
        sb = sb + ', '
      
      trav = trav.next
    
    sb = sb + ' ]'
    
    return str(sb)
