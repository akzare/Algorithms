'''
 * @file   BinarySearchTreeTest.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   27 Jun 2020
 * @version 0.1
 * @brief   A BinarySearchTree unit test.
'''

import unittest
from collections import deque
import array as arr
import random
from BinarySearchTree import TreeTraversalOrder
from BinarySearchTree import BinarySearchTree

class TestTreeNode():

  def __init__(self, data, l, r):
    self.data = data
    self.right = r
    self.left = l


def addTestTreeNode(root, data):
  """
  """
  if root is None:
    root = TestTreeNode(data, None, None)
  else:
    # Place lower elem values on left
    if data < root.data:
      root.left = addTestTreeNode(root.left, data)
    else:
      root.right = addTestTreeNode(root.right, data)

  return root


def preOrderTestTreeNode(root):
  """
  """
  lst = []
  if root is None:
    return lst

  lst.append(root.data)
  if root.left is not None:
    lst.extend(preOrderTestTreeNode(root.left))
  if root.right is not None:
    lst.extend(preOrderTestTreeNode(root.right))
    
  return lst


def inOrderTestTreeNode(root):
  """
  """
  lst = []
  if root is None:
    return lst

  if root.left is not None: 
    lst.extend(inOrderTestTreeNode(root.left))
  lst.append(root.data)
  if root.right is not None: 
    lst.extend(inOrderTestTreeNode(root.right))

  return lst


def postOrderTestTreeNode(root):
  """
  """
  lst = []
  if root is None:
    return lst

  if root.left is not None:
    lst.extend(postOrderTestTreeNode(root.left))
  if root.right is not None:
    lst.extend(postOrderTestTreeNode(root.right))
  lst.append(root.data)
  
  return lst


def levelOrderTestTreeNode(root):
  """
  """
  lst = []  
  q = deque()

  if root is not None:
    q.append(root)

  while len(q) != 0:

    root = q.popleft()
    lst.append(root.data)
    if root.left is not None:
      q.append(root.left);
    if root.right is not None:
      q.append(root.right)

  return lst




class BinarySearchTreeTest(unittest.TestCase):

  def setUp(self):
    self.LOOPS = 100


  def test_IsEmpty(self):

    tree = BinarySearchTree()
    self.assertTrue(tree.isEmpty())

    tree.add("Hello World!")
    self.assertFalse(tree.isEmpty())



  def test_Size(self):
    tree = BinarySearchTree()
    self.assertEqual(tree.size(), 0)

    tree.add("Hello World!")
    self.assertEqual(tree.size(), 1)



  def test_Height(self):
    tree = BinarySearchTree()

    # Tree should look like:
    #        M
    #      J  S
    #    B   N Z
    #  A

    # No tree
    self.assertEqual(tree.height(), 0)

    # Layer One
    tree.add("M")
    self.assertEqual(tree.height(), 1)

    # Layer Two
    tree.add("J")
    self.assertEqual(tree.height(), 2)
    tree.add("S")
    self.assertEqual(tree.height(), 2)

    # Layer Three
    tree.add("B")
    self.assertEqual(tree.height(), 3)
    tree.add("N")
    self.assertEqual(tree.height(), 3)
    tree.add("Z")
    self.assertEqual(tree.height(), 3)

    # Layer 4
    tree.add("A")
    self.assertEqual(tree.height(), 4)



  def test_Add(self):

    # Add element which does not yet exist
    tree = BinarySearchTree()
    self.assertTrue(tree.add('A'))

    # Add duplicate element
    self.assertFalse(tree.add('A'))

    # Add a second element which is not a duplicate
    self.assertTrue(tree.add('B'))



  def test_Remove(self):

    # Try removing an element which doesn't exist
    tree = BinarySearchTree()
    tree.add('A')
    self.assertEqual(tree.size(), 1)
    self.assertFalse(tree.remove('B'))
    self.assertEqual(tree.size(), 1)

    # Try removing an element which does exist
    tree.add('B')
    self.assertEqual(tree.size(), 2)
    self.assertTrue(tree.remove('B'))
    self.assertEqual(tree.size(), 1)
    self.assertEqual(tree.height(), 1)

    # Try removing the root
    self.assertTrue(tree.remove('A'))
    self.assertEqual(tree.size(), 0)
    self.assertEqual(tree.height(), 0)



  def test_Contains(self):

    # Setup tree
    tree = BinarySearchTree()

    tree.add('B')
    tree.add('A')
    tree.add('C')

    # Try looking for an element which doesn't exist
    self.assertFalse(tree.contains('D'))

    # Try looking for an element which exists in the root
    self.assertTrue(tree.contains('B'))

    # Try looking for an element which exists as the left child of the root
    self.assertTrue(tree.contains('A'))

    # Try looking for an element which exists as the right child of the root
    self.assertTrue(tree.contains('C'))


  """
  ToDo: Concurrent Modification Exceptions are not working!
  
  
  def test_concurrentModificationErrorPreOrder(self):

    bst = BinarySearchTree()

    bst.add(1)
    bst.add(2)
    bst.add(3)

    with self.assertRaises(Exception):
      for iter in bst.traverse(TreeTraversalOrder.PRE_ORDER):
        bst.add(0)


  def test_concurrentModificationErrorInOrderOrder(self):

    bst = BinarySearchTree()

    bst.add(1)
    bst.add(2)
    bst.add(3)

    with self.assertRaises(Exception):
      for iter in bst.traverse(TreeTraversalOrder.IN_ORDER):
        bst.add(0)


  def test_concurrentModificationErrorPostOrder(self):

    bst = BinarySearchTree()

    bst.add(1)
    bst.add(2)
    bst.add(3)

    with self.assertRaises(Exception):
      for iter in bst.traverse(TreeTraversalOrder.POST_ORDER):
        bst.add(0)


  def test_concurrentModificationErrorLevelOrder(self):

    bst = BinarySearchTree()

    bst.add(1)
    bst.add(2)
    bst.add(3)

    with self.assertRaises(Exception):
      for iter in bst.traverse(TreeTraversalOrder.LEVEL_ORDER):
        bst.add(0)


  def test_concurrentModificationErrorRemovingPreOrder(self):

    bst = BinarySearchTree()

    bst.add(1)
    bst.add(2)
    bst.add(3)

    with self.assertRaises(Exception):
      for iter in bst.traverse(TreeTraversalOrder.PRE_ORDER):
        bst.remove(2)


  def test_concurrentModificationErrorRemovingInOrderOrder(self):

    bst = BinarySearchTree()

    bst.add(1)
    bst.add(2)
    bst.add(3)

    with self.assertRaises(Exception):
      for iter in bst.traverse(TreeTraversalOrder.IN_ORDER):
        bst.remove(2)


  def test_concurrentModificationErrorRemovingPostOrder(self):

    bst = BinarySearchTree()

    bst.add(1)
    bst.add(2)
    bst.add(3)

    with self.assertRaises(Exception):
      for iter in bst.traverse(TreeTraversalOrder.POST_ORDER):
        bst.remove(2)

  def test_concurrentModificationErrorRemovingLevelOrder(self):

    bst = BinarySearchTree()

    bst.add(1)
    bst.add(2)
    bst.add(3)
    
    with self.assertRaises(Exception):
      for iter in bst.traverse(TreeTraversalOrder.LEVEL_ORDER):
        bst.remove(2)
  """



  def randomRemoveTests(self):

    for i in range(0, self.LOOPS):

      sz = i
      tree = BinarySearchTree()
      lst = self.genRandList(sz)
      for value in lst:
        tree.add(value)

      random.shuffle(lst)
      # Remove all the elements we just placed in the tree
      for j in range(0, sz):

        value = lst[j]

        self.assertTrue(tree.remove(value))
        self.assertFalse(tree.contains(value))
        self.assertEqual(tree.size(), sz - j - 1)

      self.assertTrue(tree.isEmpty())


  def genRandList(self, sz):
    lst = [*range(0, sz, 1)]
    random.shuffle(lst)
    return lst;


  def validateTreeTraversal(self, trav_order, input):

    out = []
    expected = []

    testTree = None
    tree = BinarySearchTree()

    # Construct Binary Tree and test tree
    for value in input:
      testTree = addTestTreeNode(testTree, value)
      tree.add(value)


    # Get traversal output
    for iter in tree.traverse(trav_order):
      out.append(iter)


    # Generate the expected output for the particular traversal
    if trav_order == TreeTraversalOrder.PRE_ORDER:
      expected = preOrderTestTreeNode(testTree)
    elif trav_order == TreeTraversalOrder.IN_ORDER:
      expected = inOrderTestTreeNode(testTree)
    elif trav_order == TreeTraversalOrder.POST_ORDER:
      expected = postOrderTestTreeNode(testTree)
    elif trav_order == TreeTraversalOrder.LEVEL_ORDER:
      expected = levelOrderTestTreeNode(testTree)
    else:
      raise Exception('Invalid TreeTraversalOrder')


    # The output and the expected size better be the same size
#    print("in ", input)
#    print("out ", out)
#    print("exp ", expected)
    if len(out) != len(expected):
      return False

    
    # Compare output to expected
    if expected != out:
      return False
    
    return True


  def test_PreOrderTraversal(self):
#    print("pre-order")
    for i in range(1, self.LOOPS):
      input = self.genRandList(i)
      self.assertTrue(self.validateTreeTraversal(TreeTraversalOrder.PRE_ORDER, input))



  def test_InOrderTraversal(self):
#    print("in-order")
    for i in range(1, self.LOOPS):
      input = self.genRandList(i)
      self.assertTrue(self.validateTreeTraversal(TreeTraversalOrder.IN_ORDER, input))


  def test_PostOrderTraversal(self):
#    print("post-order")
    for i in range(1, self.LOOPS):
      input = self.genRandList(i)
      self.assertTrue(self.validateTreeTraversal(TreeTraversalOrder.POST_ORDER, input))


  def test_LevelOrderTraversal(self):

    for i in range(1, self.LOOPS):
      input = self.genRandList(i)
      self.assertTrue(self.validateTreeTraversal(TreeTraversalOrder.LEVEL_ORDER, input))


if __name__ == '__main__':
  unittest.main()
