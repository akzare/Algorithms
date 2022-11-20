'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   20 Nov 2022

    Generate a compressed prime sieve using bit manipulation. The idea is that each bit represents a
    boolean value indicating whether a number is prime or not. This saves a lot of room when creating
    the sieve. In this implementation I store all odd numbers in individual longs meaning that for
    each long I use I can represent a range of 128 numbers (even numbers are omitted because they are
    not prime, with the exception of 2 which is handled as a special case).
    Time Complexity: ~O(nloglogn)

'''
import math


NUM_BITS = 128.0
NUM_BITS_SHIFT = 7
# 2^7 = 128
# Sets the bit representing n to 1 indicating this number is not prime

def setBit( arr,  n) :
    if ((n & 1) == 0) :
        return
    # n is even
    arr[n >> NUM_BITS_SHIFT] |= 1 << ((n - 1) >> 1)
# Returns true if the bit for n is off (meaning n is a prime).
# Note: do use this method to access numbers outside your prime sieve range!

def  isNotSet( arr,  n) :
    if (n < 2) :
        return False
    # n is not prime
    if (n == 2) :
        return True
    # two is prime
    if ((n & 1) == 0) :
        return False
    # n is even
    chunk = arr[n >> NUM_BITS_SHIFT]
    mask = 1 << ((n - 1) >> 1)
    return (chunk & mask) != mask
# Returns true/false depending on whether n is prime.

def  isPrime( sieve,  n) :
    return isNotSet(sieve, n)
# Returns an array of longs with each bit indicating whether a number
# is prime or not. Use the isNotSet and setBit methods to toggle to bits for each number.

def  primeSieve( limit) :
    numChunks = int(math.ceil(limit / NUM_BITS))
    sqrtLimit = int(math.sqrt(limit))
    # if (limit < 2) return 0; // uncomment for primeCount purposes
    # int primeCount = (int) Math.ceil(limit / 2.0); // Counts number of primes <= limit
    chunks = [0] * (numChunks)
    chunks[0] = 1
    # 1 as not prime
    i = 3
    while (i <= sqrtLimit) :
        if (isNotSet(chunks, i)) :
            j = i * i
            while (j <= limit) :
                if (isNotSet(chunks, j)) :
                    setBit(chunks, j)
                j += i
        i += 2
    return chunks
# Example usage.


limit = 200
sieve = primeSieve(limit)
i = 0
while (i <= limit) :
    if (isPrime(sieve, i)) :
        print("%d is prime!\n" % (i),end ="",sep ="")
    i += 1

