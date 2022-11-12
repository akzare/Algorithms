'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   11 Nov 2022

    Test to see whether two numbers are relatively prime (coprime).
    Time Complexity: O(log(a+b))

'''

import math

def gcf(a,b):
    if b==0:
        return a
    else:
        return gcf(b,a%b)
    
def areCoprime(a,b):
    return gcf(a,b)==1

if __name__=='__main__':
    print(areCoprime(5,7))
    print(areCoprime(12,18))
