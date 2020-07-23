'''
 * @file   BinarySearchTree.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   26 Jun 2020
 * @version 0.1
 * @brief   Binary Search Tree (BST) data structure implementation.
 * This file contains an implementation of a Binary Search Tree (BST) Any comparable data is allowed
 * within this tree (numbers, strings, comparable Objects, etc...). Supported operations include
 * adding, removing, height, and containment checks. Furthermore, multiple tree traversal Iterators
 * are provided including: 1) Preorder traversal 2) Inorder traversal 3) Postorder traversal 4)
 * Levelorder traversal
'''
from collections import deque
#from multipledispatch import dispatch

from array import array as arr
from enum import Enum, auto

class TreeTraversalOrder(Enum):
  PRE_ORDER = auto()
  IN_ORDER = auto()
  POST_ORDER = auto()
  LEVEL_ORDER = auto()


class Node():
  """
  Internal node containing node references
  and the actual node data
  """
  def __init__(self, left, right, elem):
    self.data = elem
    self.left = left
    self.right = right


class BinarySearchTree():
  ''' 
  An implementation of an indexed binary heap priority queue.
  '''
  def __init__(self):

    # Tracks the number of nodes in this BST
    self.nodeCount = 0

    # This BST is a rooted tree so we maintain a handle on the root node
    self.root = None
    
    self.stackPreOrderIter = deque()


  def isEmpty(self):
    """
    Check if this binary tree is empty
    """
    return self.size() == 0


  def size(self):
    """
    Get the number of nodes in this binary tree
    """
    return self.nodeCount


  def add(self, elem):
    """
    Add an element to this binary tree. Returns true
    if we successfully perform an insertion
    """

    # Check if the value already exists in this
    # binary tree, if it does ignore adding it
    if self.contains(elem):
      return False

    # Otherwise add this element to the binary tree
    else:
      self.root = self.__add(self.root, elem)
      self.nodeCount += 1
      return True


  def __add(self, node, elem):

    # Base case: found a leaf node
    if node == None:
      node = Node(None, None, elem)

    else:
      # Pick a subtree to insert element
      if elem < node.data:
        node.left = self.__add(node.left, elem)
      else:
        node.right = self.__add(node.right, elem)

    return node


  def remove(self, elem):
    """
    Remove a value from this binary tree if it exists, O(n)
    """
    # Make sure the node we want to remove
    # actually exists before we remove it
    if self.contains(elem):
      self.root = self.__remove(self.root, elem)
      self.nodeCount -= 1
      return True

    return False


  def __remove(self, node, elem):

    if node == None:
      return None

    cmp = elem < node.data
    
    if elem == node.data:

      # This is the case with only a right subtree or
      # no subtree at all. In this situation just
      # swap the node we wish to remove with its right child.
      if node.left == None:

        rightChild = node.right

        node.data = None
        node = None

        return rightChild

        # This is the case with only a left subtree or
        # no subtree at all. In this situation just
        # swap the node we wish to remove with its left child.
      elif node.right == None:

        leftChild = node.left

        node.data = None
        node = None

        return leftChild

        # When removing a node from a binary tree with two links the
        # successor of the node being removed can either be the largest
        # value in the left subtree or the smallest value in the right
        # subtree. In this implementation I have decided to find the
        # smallest value in the right subtree which can be found by
        # traversing as far left as possible in the right subtree.
      else:

        # Find the leftmost node in the right subtree
        tmp = self.findMin(node.right)

        # Swap the data
        node.data = tmp.data

        # Go into the right subtree and remove the leftmost node we
        # found and swapped data with. This prevents us from having
        # two nodes in our tree with the same value.
        node.right = self.__remove(node.right, tmp.data)

        # If instead we wanted to find the largest node in the left
        # subtree as opposed to smallest node in the right subtree
        # here is what we would do:
        # Node tmp = findMax(node.left);
        # node.data = tmp.data;
        # node.left = self.__remove(node.left, tmp.data);

    # Dig into left subtree, the value we're looking
    # for is smaller than the current value
    elif cmp is True:
      node.left = self.__remove(node.left, elem)

      # Dig into right subtree, the value we're looking
      # for is greater than the current value
    elif cmp is False:
      node.right = self.__remove(node.right, elem)

      # Found the node we wish to remove
    else:
      return None

    return node


  def findMin(self, node):
    """
    Helper method to find the leftmost node (which has the smallest value)
    """
    while node.left is not None:
      node = node.left;
    return node


  def findMax(self, node):
    """
    Helper method to find the rightmost node (which has the largest value)
    """
    while node.right is not None:
      node = node.right
    return node


  def contains(self, elem):
    """
    returns true is the element exists in the tree
    """
    return self.__contains(self.root, elem)


  def __contains(self, node, elem):
    """
    private recursive method to find an element in the tree
    """

    # Base case: reached bottom, value not found
    if node == None:
      return False

    cmp = elem < node.data

    if elem == node.data:
      return True

    # Dig into the left subtree because the value we're
    # looking for is smaller than the current value
    elif cmp is True:
      return self.__contains(node.left, elem)

    # Dig into the right subtree because the value we're
    # looking for is greater than the current value
    elif cmp is False:
      return self.__contains(node.right, elem)

    # We found the value we were looking for
    else:
      return True


  def height(self):
    """
    Computes the height of the tree, O(n)
    """
    return self.__height(self.root)


  def __height(self, node):
    """
    Recursive helper method to compute the height of the tree
    """
    if node == None:
      return 0
    return max(self.__height(node.left), self.__height(node.right)) + 1


  def traverse(self, order):
    """
    This method returns an iterator for a given TreeTraversalOrder.
    The ways in which you can traverse the tree are in four different ways:
    preorder, inorder, postorder and levelorder.
    """

    if order is TreeTraversalOrder.PRE_ORDER:
      return self.preOrderTraversal()
    if order is TreeTraversalOrder.IN_ORDER:
      return self.inOrderTraversal()
    if order is TreeTraversalOrder.POST_ORDER:
      return self.postOrderTraversal()
    if order is TreeTraversalOrder.LEVEL_ORDER:
      return self.levelOrderTraversal()

    return None


  def __iter__(self): 
    """
     Called when iteration is initialized
     Returns as iterator to traverse the tree in pre order
    """
    self.expectedNodeCount = self.nodeCount
    self.stackPreOrderIter.clear()
    self.stackPreOrderIter.append(self.root)
    return self


  def __next__(self): 
    """
    To move to next element. 
    """
    # ToDo: Concurrent Modification Exceptions are not working!
    if self.expectedNodeCount != self.nodeCount:
      raise Exception('ConcurrentModificationException')
    
    if self.root == None or len(self.stackPreOrderIter) == 0:
      raise StopIteration 

    node = self.stackPreOrderIter.popleft()
    if node.right != None:
      self.stackPreOrderIter.append(node.right)
    if node.left != None:
      self.stackPreOrderIter.append(node.left)
    return node.data


  def preOrderTraversal(self):
    """
    Returns as iterator to traverse the tree in pre order
    """
    if self.root is None:
      return None
        
    expectedNodeCount = self.nodeCount
    stack = deque()
    stack.append(self.root)

    trav = self.root
    while True:
      if self.root is None or len(stack) == 0:
        break

      node = stack.pop()
      if node.right is not None:
        stack.append(node.right)
      if node.left is not None:
        stack.append(node.left)

      yield node.data
    else:
      raise StopIteration


  def inOrderTraversal(self):
    """
    Returns as iterator to traverse the tree in order
    """
    expectedNodeCount = self.nodeCount
    stack = deque()
    stack.append(self.root)
    trav = self.root
    while True:
      if self.root == None or len(stack) == 0:
        break
        
      # Dig left
      while trav != None and trav.left != None:
        stack.append(trav.left)
        trav = trav.left

      node = stack.pop()

      # Try moving down right once
      if node.right != None:
        stack.append(node.right)
        trav = node.right

      yield node.data
    else:
      raise StopIteration


  def postOrderTraversal(self):
    """
    Returns as iterator to traverse the tree in post order
    """
    expectedNodeCount = self.nodeCount
    stack1 = deque()
    stack1.append(self.root)
    stack2 = deque()
    
    while len(stack1) != 0:
      node = stack1.pop()
      if node is not None:
        stack2.append(node)
        if node.left is not None:
          stack1.append(node.left)
        if node.right is not None:
          stack1.append(node.right);

    while True:
      if self.root == None or len(stack2) == 0:
        break

      node = stack2.pop()

      yield node.data
    else:
      raise StopIteration


  def levelOrderTraversal(self):
    """
    Returns as iterator to traverse the tree in level order
    """
    expectedNodeCount = self.nodeCount
    queue = deque()
    queue.append(self.root)

    while True:
      if self.root == None or len(queue) == 0:
        break

      node = queue.popleft()
      if node.left is not None:
        queue.append(node.left)
      if node.right is not None:
        queue.append(node.right)

      yield node.data
    else:
      raise StopIteration
