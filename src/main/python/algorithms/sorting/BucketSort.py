'''
 * @file   BucketSort.py
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Armin Zare Zadeh, ali.a.zarezadeh@gmail.com
 * @date   27 Jun 2020
 * @version 0.1
 * @brief   Bucket sort implementation
'''

import sys

class BucketSort():

  def __init__(self):
    pass


  def sort(self, values):
    minValue = sys.maxsize
    maxValue = -sys.maxsize - 1
    for i in range(0, len(values)):
      if values[i] < minValue:
        minValue = values[i]
      if values[i] > maxValue:
        maxValue = values[i]

    self.bucketSort(values, minValue, maxValue)


  def bucketSort(self, ar, minValue, maxValue):
    """
    Performs a bucket sort of an array in which all the elements are
    bounded in the range [minValue, maxValue]. For bucket sort to give linear
    performance the elements need to be uniformly distributed
    """
    if ar == None or len(ar) == 0 or minValue == maxValue:
      return None

    # N is number elements and M is the range of values
    N = len(ar)
    M = maxValue - minValue + 1
    numBuckets = M // N + 1
    buckets = []
    for i in range(0, numBuckets):
      buckets.append([])

    # Place each element in a bucket
    for  i in range(0, N):
      bi = (ar[i] - minValue) // M
      buckets[bi].append(ar[i])


    # Sort buckets and stitch together answer
    j = 0
    for bi in range(0, numBuckets):
      bucket = buckets[bi]
      if bucket is not None:
        bucket.sort()
        for k in range(0, len(bucket)):
          ar[j] = bucket[k]
          j += 1



if __name__ == '__main__':
  """
  Example usage
  """
  sorter = BucketSort()

  array = [10, 4, 6, 8, 13, 2, 3]
  sorter.sort(array)
  # Prints:
  # [2, 3, 4, 6, 8, 10, 13]
  print(array)

  array = [10, 10, 10, 10, 10]
  sorter.sort(array);
  # Prints:
  # [10, 10, 10, 10, 10]
  print(array)
