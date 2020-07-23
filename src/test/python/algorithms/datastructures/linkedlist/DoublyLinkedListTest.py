'''
 * @file   DoublyLinkedListTest.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   20 Jun 2020
 * @version 0.1
 * @brief   A doubly linked list unit test.
'''

import unittest
from collections import deque
import random
from DoublyLinkedList import DoublyLinkedList

class LinkedListTest(unittest.TestCase):

  def setUp(self):
    self.LOOPS = 10000
    self.TEST_SZ = 40
    self.NUM_NULLS = int(self.TEST_SZ / 5)
    self.MAX_RAND_NUM = 250
          
    self.lnkList = DoublyLinkedList()


  def tearDown(self):
    self.lnkList.clear()


  def test_EmptyList(self):
    self.assertTrue(self.lnkList.isEmpty())
    self.assertEqual(self.lnkList.size(), 0)


  def test_RemoveFirstOfEmpty(self):
    with self.assertRaises(Exception):
      self.lnkList.removeFirst()


  def test_RemoveLastOfEmpty(self):
    with self.assertRaises(Exception):
      self.lnkList.removeLast()


  def test_PeekFirstOfEmpty(self):
    with self.assertRaises(Exception):
      self.lnkList.peekFirst()


  def test_PeekLastOfEmpty(self):
    with self.assertRaises(Exception):
      self.lnkList.peekLast()


  def test_AddFirst(self):
    self.lnkList.addFirst(3)
    self.assertEqual(self.lnkList.size(), 1)
    self.lnkList.addFirst(5)
    self.assertEqual(self.lnkList.size(), 2)


  def test_AddLast(self):
    self.lnkList.addLast(3)
    self.assertEqual(self.lnkList.size(), 1)
    self.lnkList.addLast(5)
    self.assertEqual(self.lnkList.size(), 2)


  def test_AddAt(self):
    self.lnkList.addAt(0, 1)
    self.assertEqual(self.lnkList.size(), 1)
    self.lnkList.addAt(1, 2)
    self.assertEqual(self.lnkList.size(), 2)
    self.lnkList.addAt(1, 3)
    self.assertEqual(self.lnkList.size(), 3)
    self.lnkList.addAt(2, 4)
    self.assertEqual(self.lnkList.size(), 4)
    self.lnkList.addAt(1, 8)
    self.assertEqual(self.lnkList.size(), 5)


  def test_RemoveFirst(self):
    self.lnkList.addFirst(3)
    self.assertTrue(self.lnkList.removeFirst() == 3)
    self.assertTrue(self.lnkList.isEmpty())


  def test_RemoveLast(self):
    self.lnkList.addLast(4)
    self.assertTrue(self.lnkList.removeLast() == 4)
    self.assertTrue(self.lnkList.isEmpty())



  def test_PeekFirst(self):
    self.lnkList.addFirst(4)
    self.assertTrue(self.lnkList.peekFirst() == 4)
    self.assertEqual(self.lnkList.size(), 1)


  def test_PeekLast(self):
    self.lnkList.addLast(4)
    self.assertTrue(self.lnkList.peekLast() == 4)
    self.assertEqual(self.lnkList.size(), 1)


  def test_Peeking(self):
    # 5
    self.lnkList.addFirst(5)
    self.assertTrue(self.lnkList.peekFirst() == 5)
    self.assertTrue(self.lnkList.peekLast() == 5)

    # 6 - 5
    self.lnkList.addFirst(6);
    self.assertTrue(self.lnkList.peekFirst() == 6);
    self.assertTrue(self.lnkList.peekLast() == 5);

    # 7 - 6 - 5
    self.lnkList.addFirst(7)
    self.assertTrue(self.lnkList.peekFirst() == 7)
    self.assertTrue(self.lnkList.peekLast() == 5)

    # 7 - 6 - 5 - 8
    self.lnkList.addLast(8)
    self.assertTrue(self.lnkList.peekFirst() == 7)
    self.assertTrue(self.lnkList.peekLast() == 8)

    # 7 - 6 - 5
    self.lnkList.removeLast()
    self.assertTrue(self.lnkList.peekFirst() == 7)
    self.assertTrue(self.lnkList.peekLast() == 5)

    # 7 - 6
    self.lnkList.removeLast()
    self.assertTrue(self.lnkList.peekFirst() == 7)
    self.assertTrue(self.lnkList.peekLast() == 6)

    # 6
    self.lnkList.removeFirst()
    self.assertTrue(self.lnkList.peekFirst() == 6)
    self.assertTrue(self.lnkList.peekLast() == 6)


  def test_Removing(self):
    strs = DoublyLinkedList()
    strs.add("a")
    strs.add("b")
    strs.add("c")
    strs.add("d")
    strs.add("e")
    strs.add("f")
    strs.remove("b")
    strs.remove("a")
    strs.remove("d")
    strs.remove("e")
    strs.remove("c")
    strs.remove("f")
    self.assertEqual(0, strs.size())
    strs.clear()



  def test_RemoveAt(self):
    self.lnkList.add(1)
    self.lnkList.add(2)
    self.lnkList.add(3)
    self.lnkList.add(4)
    self.lnkList.removeAt(0)
    self.lnkList.removeAt(2)
    print(self.lnkList.peekFirst())
    self.assertTrue(self.lnkList.peekFirst() == 2)
    self.assertTrue(self.lnkList.peekLast() == 3)
    self.lnkList.removeAt(1)
    self.lnkList.removeAt(0)
    self.assertEqual(self.lnkList.size(), 0)



  def test_Clear(self):
    self.lnkList.add(22)
    self.lnkList.add(33)
    self.lnkList.add(44)
    self.assertEqual(self.lnkList.size(), 3)
    self.lnkList.clear()
    self.assertEqual(self.lnkList.size(), 0)
    self.lnkList.add(22)
    self.lnkList.add(33)
    self.lnkList.add(44)
    self.assertEqual(self.lnkList.size(), 3)
    self.lnkList.clear()
    self.assertEqual(self.lnkList.size(), 0)



  def test_RandomizedRemoving(self):
    pythonLinkedList = deque()
    for loops in range(0, self.LOOPS):

      self.lnkList.clear();
      pythonLinkedList.clear();

      randNums = self.genRandList(self.TEST_SZ)
      for value in randNums:
        pythonLinkedList.append(value)
        self.lnkList.add(value)

      random.shuffle(randNums)

      for i in range(0, len(randNums)):    
        rm_val = randNums[i]
        self.assertEqual(pythonLinkedList.remove(rm_val), None)
        self.assertEqual(self.lnkList.remove(rm_val), True)
        self.assertEqual(len(pythonLinkedList), self.lnkList.size())
        

        iter1 = iter(pythonLinkedList)
        iter2 = iter(self.lnkList)
        
        while True:
          pyVal = next(iter1, -1)
          if pyVal == -1: break
          llVal = next(iter2, -1)
          self.assertEqual(pyVal, llVal)



  def test_RandomizedRemoveAt(self):
    pythonLinkedList = deque()
    for loops in range(0, self.LOOPS):

      self.lnkList.clear()
      pythonLinkedList.clear()

      randNums = self.genRandList(self.TEST_SZ)

      for value in randNums:          
        pythonLinkedList.append(value)
        self.lnkList.add(value)

      for i in range(0, len(randNums)):    

        rm_index = random.sample(range(0, self.lnkList.size()), 1)
        rm_index = rm_index[0]
        
        num1 = pythonLinkedList[rm_index]
        num2 = self.lnkList.removeAt(rm_index)
        del pythonLinkedList[rm_index]

        self.assertEqual(num1, num2);
        self.assertEqual(len(pythonLinkedList), self.lnkList.size())

        iter1 = iter(pythonLinkedList)
        iter2 = iter(self.lnkList)
        
        while True:
          pyVal = next(iter1, -1)
          if pyVal == -1: break
          llVal = next(iter2, -1)
          self.assertEqual(pyVal, llVal)       

  
  def test_RandomizedIndexOf(self):
    pythonLinkedList = deque()
    for loops in range(0, self.LOOPS):

      self.lnkList.clear()
      pythonLinkedList.clear()

      randNums = self.genUniqueRandList(self.TEST_SZ)

      for value in randNums:          
        pythonLinkedList.append(value)
        self.lnkList.add(value)

      random.shuffle(randNums)

      for i in range(0, len(randNums)):    
        elem = randNums[i]
        index1 = pythonLinkedList.index(elem)
        index2 = self.lnkList.indexOf(elem)

        self.assertEqual(index1, index2);
        self.assertEqual(len(pythonLinkedList), self.lnkList.size())

        iter1 = iter(pythonLinkedList)
        iter2 = iter(self.lnkList)
        
        while True:
          pyVal = next(iter1, -1)
          if pyVal == -1: break
          llVal = next(iter2, -1)
          self.assertEqual(pyVal, llVal)       



  def testToString(self):
    strs = DoublyLinkedList()
    self.assertEqual(str(strs), "[  ]")
    strs.add("a")
    self.assertEqual(str(strs), "[ a ]")
    strs.add("b")
    self.assertEqual(str(strs), "[ a, b ]")
    strs.add("c")
    strs.add("d")
    strs.add("e")
    strs.add("f")
    self.assertEqual(str(strs), "[ a, b, c, d, e, f ]");



  def genRandList(self, sz):
    """
    Generate a list of random numbers
    """   
    #Generate sz random numbers between 0 and MAX_RAND_NUM
    lst = random.sample(range(0, self.MAX_RAND_NUM), sz)

    for i in range(0, self.NUM_NULLS):
      lst.append(None)

    random.shuffle(lst)
    return lst


  def genUniqueRandList(self, sz):
    """
    Generate a list of unique random numbers
    """
    lst = [*range(0, sz, 1)]
    for i in range(0, self.NUM_NULLS):
      lst.append(None)
    random.shuffle(lst)
    return lst



if __name__ == '__main__':
  unittest.main()