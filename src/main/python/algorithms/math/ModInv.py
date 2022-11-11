'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   11 Nov 2022

    
    An implementation of the modPow(a, n, mod) operation.
    Time Complexity O(lg(n))

'''

import math


# This function performs the extended euclidean algorithm on two numbers a and b.
# The function returns the gcd(a,b) as well as the numbers x and y such
# that ax + by = gcd(a,b). This calculation is important in number theory
# and can be used for several things such as finding modular inverses and
# solutions to linear Diophantine equations.


def egcd(a, b):
    if b == 0:
        return (a, 1, 0)
    else:
        g, y, x = egcd(b, a % b)
        return (g, x, y - (a // b) * x)


#  Returns the modular inverse of 'a' mod 'm'
#  Make sure m > 0 and 'a' & 'm' are relatively prime.
def modInv(a, m):

    if m < 0:
        raise Exception(' mod must be > 0')
    a = ((a % m)+m) % m
    g, x, y = egcd(a, m)
    if g != 1:
        return None
    return ((x % m)+m) % m


print(modInv(2, 5))  # 2*3 mod 5=1
print(modInv(4, 18))  # 4*x mod 18=1
