'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   11 Nov 2022

    
    An implementation of finding the GCD of two numbers. Time Complexity: Time Complexity ~O(log(a + b))

'''

def gcd(a,b):
    if a<0:
        a=-a
    if b==0:
        return a
    else:
        return gcd(b,a%b)

if __name__=='__main__':
    print(gcd(12, 18))   # 6
    print(gcd(-12, 18))  # 6
    print(gcd(12, -18))  # 6
    print(gcd(-12, -18)) # 6
    print(gcd(5, 0))     # 5
    print(gcd(0, 5))     # 5
    print(gcd(-5, 0))    # 5
    print(gcd(0, -5))    # 5
    print(gcd(0, 0))     # 0