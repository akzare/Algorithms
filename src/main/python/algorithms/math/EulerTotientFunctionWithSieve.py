'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   20 Nov 2022

    Computes Euler's totient function

'''

import math

def  sieve( limit) :
    if (limit <= 2) :
        return [0] * (0)

    numPrimes = int((1.25506 * limit / math.log(float(limit))))
    primes = [0] * (numPrimes)
    index = 0
    isComposite = [False] * (limit)
    sqrtLimit = int(math.sqrt(limit))
    i = 2
    while (i <= sqrtLimit) :
        if (not isComposite[i]) :
            primes[index] = i
            index += 1
            j = i * i
            while (j < limit) :
                isComposite[j] = True
                j += i
        i += 1
    i = sqrtLimit + 1
    while (i < limit) :
        if (not isComposite[i]) :
            primes[index] = i
            index += 1
        i += 1
    return primes[:index]


MAX = 1000000
PRIMES = sieve(MAX)


def  totient(n) :
    if (n >= MAX - 1) :
        raise Exception("MAX not large enough!")
    ans = n
    i = 1
    p = PRIMES[0]
    while (p * p <= n) :
        if (n % p == 0) :
            ans -= int(ans / p)
        while (n % p == 0) :
            n /= p
        p = PRIMES[i]
        i += 1
    # Last factor
    if (n != 1) :
        ans -= int(ans / n)
    return ans



# Prints 8 because 1,2,4,7,8,11,13,14 are all
# less than 15 and relatively prime with 15
print(totient(15))
x = 1
while (x <= 11) :
    print("phi(%d) = %d\n" % (x,totient(x)),end ="",sep ="")
    x += 1
