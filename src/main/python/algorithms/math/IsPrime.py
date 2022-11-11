'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   11 Nov 2022

    Tests whether a number is a prime number or not Time Complexity: O(sqrt(n))

'''



import math

def isPrime(n):
    if n<2:
        return False
    if (n==2)or(n==3):
        return True
    if n%2==0 or n%3==0:
        return False

    limit=int(math.sqrt(n))
    for i in range(5,limit+1,6):
        if n%i==0 or (n%(i+2)==0):
            return False
    
    return True

print(isPrime(5))
print(isPrime(31))
print(isPrime(1433))
print(isPrime(8763857775536878331))

    
    
