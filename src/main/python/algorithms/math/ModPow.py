'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   11 Nov 2022

    
    An implementation of the modPow(a, n, mod) operation.
    Time Complexity O(lg(n))

'''

import math


# Computes the Greatest Common Divisor (GCD) of a & b
def gcd(a, b):
    if a < 0:
        a = -a
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

# This function performs the extended euclidean algorithm on two numbers a and b.
# The function returns the gcd(a,b) as well as the numbers x and y such
# that ax + by = gcd(a,b). This calculation is important in number theory
# and can be used for several things such as finding modular inverses and
# solutions to linear Diophantine equations.


def egcd(a, b):
    if a < 0:
        a = -a
    if b == 0:
        return (b, 1, 0)
    else:
        g, y, x = egcd(b, a % b)
        return (g, x, y - (a // b) * x)


#  Returns the modular inverse of 'a' mod 'm'
#  Make sure m > 0 and 'a' & 'm' are relatively prime.
def modInv(a, m):

    a = ((a % m)+m) % m
    g, x, y = egcd(a, m)
    return ((x % m)+m) % m

# Computes a^n modulo mod very efficiently in O(lg(n)) time.
# This function supports negative exponent values and a negative
# base, however the modulus must be positive.


def modPow(a, n, mod):
    if mod < 0:
        raise Exception('mod must be positive')

    # To handle negative exponents we can use the modular
    # inverse of a to our advantage since: a^-n mod m = (a^-1)^n mod m

    if n < 0:
        if gcd(a, mod) != 1:
            raise Exception("If n < 0 then must have gcd(a, mod) = 1")
        return modPow(modInv(a, mod), -n, mod)
    if n == 0:
        return 1
    p = a
    r = 1
    i = 0
    while n != 0:
        mask = 1 << i
        if n & mask == mask:
            r = (((r * p) % mod) + mod) % mod
            n -= mask
        p = ((p * p) % mod + mod) % mod
        i+=1
    return ((r % mod) + mod) % mod


# 3 ^ 4 mod 1000000
    
r1 = modPow(3, 4, 10**6) #81
r2 = modPow(-45, 12345, 987654321) #323182557
r3 = modPow(6, -66, 101) #84
r4 = modPow(-5, -7, 1009) #675

print(r1,r2,r3,r4)