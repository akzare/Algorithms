'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   11 Nov 2022

    Test to see whether two numbers are relatively prime (coprime).
    Time Complexity: O(log(a+b))

'''

import math

def sieve(limit):
    if limit<2: return []
    numPrimes=(int)(1.25506*limit/math.log(float(limit)))
    primes=[]*numPrimes
    index=0
    isComp= []*limit
    sqrtlimit=int(math.sqrt(limit))
    for i in range(2,sqrtlimit+1):
        if(not isComp[i]):
            primes[index]=1
            index+=1
            for j in range(i*i,limit):
                isComp[j]=True
    for i in range(sqrtlimit+1,i<limit):
        if not isComp[i]:
            primes[index]=i
            index+=1
    return primes[:index]

print(sieve(29))