import math
import random
import queue

def  eulersTotient( n) :
    for p in  set() :
        n -= (n / p)
    return n

def  primeFactorization( n) :
    factors =  []
    if (n <= 0) :
        raise Exception("IllegalArgumentException")
    elif(n == 1) :
        return factors
    divisorQueue =  queue.PriorityQueue()
    divisorQueue.add(n)
    while (not divisorQueue.isEmpty()) :
        divisor = divisorQueue.remove()
        if (isPrime(divisor)) :
            factors.append(divisor)
            continue
        next_divisor = pollardRho(divisor)
        if (next_divisor == divisor) :
            divisorQueue.add(divisor)
        else :
            divisorQueue.add(next_divisor)
            divisorQueue.add(divisor / next_divisor)
    return factors

def  pollardRho( n) :
    if (n % 2 == 0) :
        return 2
    # Get a number in the range [2, 10^6]
    x = 2 + int((999999 * random.random()))
    c = 2 + int((999999 * random.random()))
    y = x
    d = 1
    while (d == 1) :
        x = (x * x + c) % n
        y = (y * y + c) % n
        y = (y * y + c) % n
        d = gcf(abs(x - y), n)
        if (d == n) :
            break
    return d

def  gcf( a,  b) :
    return a if b == 0 else gcf(b, a % b)

def  isPrime( n) :
    if (n < 2) :
        return False
    if (n == 2 or n == 3) :
        return True
    if (n % 2 == 0 or n % 3 == 0) :
        return False
    limit = int(math.sqrt(n))
    i = 5
    while (i <= limit) :
        if (n % i == 0 or n % (i + 2) == 0) :
            return False
        i += 6
    return True

def main( args) :
    # Prints 8 because 1,2,4,7,8,11,13,14 are all
    # less than 15 and relatively prime with 15
    print("phi(15) = %d\n" % (eulersTotient(15)),end ="",sep ="")
    print()
    x = 1
    while (x <= 11) :
        print("phi(%d) = %d\n" % (x,eulersTotient(x)),end ="",sep ="")
        x += 1
    
