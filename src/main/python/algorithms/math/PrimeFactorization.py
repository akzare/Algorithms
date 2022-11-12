'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   11 Nov 2022

    
    

'''

import math
import random
# from PriorityQueue import PriorityQueueSet
import queue
import IsPrime
import GCD


def primeFactors(n):
    fact = []
    if n <= 0:
        raise ValueError("n must be positive")
    elif n == 1:
        return fact
    a = [0]
    # pq=PriorityQueueSet(items=a)
    pq = queue.PriorityQueue()
    pq.put(n)
    while not pq.empty():
        divisor = pq.get()
        if (IsPrime.isPrime(divisor)):
            fact.append(divisor)
            continue
        next_divisor = pollarRho(divisor)
        if next_divisor == divisor:
            pq.put(int(divisor))
        else:
            pq.put(int(next_divisor))
            pq.put(int(divisor/next_divisor))

    return fact


def pollarRho(n):
    if n % 2 == 0:
        return 2
    x = 2+(int)(999999*random.random())
    c = 2+(int)(999999*random.random())
    y = 2+(int)(999999*random.random())
    y = x
    d = 1
    while (d == 1):
        x = (x * x + c) % n
        y = (y * y + c) % n
        y = (y * y + c) % n
        d = GCD.gcd(abs(x - y), n)
        if d == n:
            break
    return d


if __name__ == '__main__':
    print(primeFactors(7))  # [7]
    print(primeFactors(100))  # [2, 2, 5, 5]
    print(primeFactors(666))  # [2, 3, 3, 37]
    print(primeFactors(872342345))  # [5, 7, 7, 19, 67, 2797]
