'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   11 Nov 2022

    
    Calculate the value of C(N, R) % P using Fermat's Little Theorem.
    Time Complexity O(lg(n))

'''

import math
import ModInv

def compute(n,r,p):
    if r==0:return 1
    fact=[None]*(n+1)
    fact[0]=1

    for i in range(1,n+1):
        fact[i]=fact[i-1]*i%p
    
    return (fact[n]*ModInv.modInv(fact[r],p)%p*ModInv.modInv(fact[n-r],p)%p)%p


z=compute(500,250,1000000007)
print(z) #515561345