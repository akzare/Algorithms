'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   20 Nov 2022

    This function performs the extended euclidean algorithm on two numbers a and b.
    The function returns the gcd(a,b) as well as the numbers x and y such
    that ax + by = gcd(a,b). This calculation is important in number theory
    and can be used for several things such as finding modular inverses and
    solutions to linear Diophantine equations.
    Time Complexity ~O(log(a + b))

'''

def egcd(a,b):
    if b==0:
        return {a,1,0}
    else:
        ret=egcd(b,a%b)
        tmp=ret[1]-ret[2]*(a/b)
        ret[1]=ret[2]
        ret[2]=tmp
        return ret
