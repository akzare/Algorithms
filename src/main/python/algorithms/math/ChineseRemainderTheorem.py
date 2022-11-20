'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   20 Nov 2022

    Use the chinese remainder theorem to solve a set of congruence equations.

    <p>The first method (eliminateCoefficient) is used to reduce an equation of the form cx≡a(mod
    m)cx≡a(mod m) to the form x≡a_new(mod m_new)x≡anew(mod m_new), which gets rids of the
    coefficient. A value of null is returned if the coefficient cannot be eliminated.

    <p>The second method (reduce) is used to reduce a set of equations so that the moduli become
    pairwise co-prime (which means that we can apply the Chinese Remainder Theorem). The input and
    output are of the form x≡a_0(mod m_0),...,x≡a_n-1(mod m_n-1)x≡a_0(mod m_0),...,x≡a_n-1(mod
    m_n-1). Note that the number of equations may change during this process. A value of null is
    returned if the set of equations cannot be reduced to co-prime moduli.

    <p>The third method (crt) is the actual Chinese Remainder Theorem. It assumes that all pairs of
    moduli are co-prime to one another. This solves a set of equations of the form x≡a_0(mod
    m_0),...,x≡v_n-1(mod m_n-1)x≡a_0(mod m_0),...,x≡v_n-1(mod m_n-1). It's output is of the form
    x≡a_new(mod m_new)x≡a_new(mod m_new).


'''

import math
import queue
import random

# eliminateCoefficient() takes cx?a(mod m) and gives x?a_new(mod m_new).

def  eliminateCoefficient( c,  a,  m) :
    d = egcd(c, m)[0]
    if (a % d != 0) :
        return None
    c /= d
    a /= d
    m /= d
    inv = egcd(c, m)[1]
    m = abs(m)
    a = (((a * inv) % m) + m) % m
    return [a, m]
# reduce() takes a set of equations and reduces them to an equivalent
# set with pairwise co-prime moduli (or null if not solvable).

def  reduce( a,  m) :
    aNew =  []
    mNew =  []
    # Split up each equation into prime factors
    i = 0
    while (i < len(a)) :
        factors = primeFactorization(m[i])
        factors.sort()
        iterator = factors.listIterator()
        while (iterator.hasNext()) :
            val = iterator.next()
            total = val
            while (iterator.hasNext()) :
                nextVal = iterator.next()
                if (nextVal == val) :
                    total *= val
                else :
                    iterator.previous()
                    break
            aNew.add(a[i] % total)
            mNew.add(total)
        i += 1
    # Throw away repeated information and look for conflicts
    i = 0
    while (i < aNew.size()) :
        j = i + 1
        while (j < aNew.size()) :
            if (mNew.get(i) % mNew.get(j) == 0 or mNew.get(j) % mNew.get(i) == 0) :
                if (mNew.get(i) > mNew.get(j)) :
                    if ((aNew.get(i) % mNew.get(j)) == aNew.get(j)) :
                        aNew.remove(j)
                        mNew.remove(j)
                        j -= 1
                        continue
                    else :
                        return None
                else :
                    if ((aNew.get(j) % mNew.get(i)) == aNew.get(i)) :
                        aNew.remove(i)
                        mNew.remove(i)
                        i -= 1
                        break
                    else :
                        return None
            j += 1
        i += 1
    # Put result into an array
    res = [[0] * (aNew.size()) for _ in range(2)]
    i = 0
    while (i < aNew.size()) :
        res[0][i] = aNew.get(i)
        res[1][i] = mNew.get(i)
        i += 1
    return res

def  crt( a,  m) :
    M = 1
    i = 0
    while (i < len(m)) :
        M *= m[i]
        i += 1
    inv = [0] * (len(a))
    i = 0
    while (i < len(inv)) :
        inv[i] = egcd(M / m[i], m[i])[1]
        i += 1
    x = 0
    i = 0
    while (i < len(m)) :
        x += (M / m[i]) * a[i] * inv[i]
        # Overflow could occur here
        x = ((x % M) + M) % M
        i += 1
    return [x, M]

def  primeFactorization( n) :
    factors =  []
    if (n <= 0) :
        raise Exception("IllegalArgumentException")
    elif(n == 1) :
        return factors
    divisorQueue = queue.PriorityQueue()
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
# Extended euclidean algorithm

def  egcd( a,  b) :
    if (b == 0) :
        return [a, 1, 0]
    else :
        ret = egcd(b, a % b)
        tmp = ret[1] - ret[2] * (a / b)
        ret[1] = ret[2]
        ret[2] = tmp
        return ret

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