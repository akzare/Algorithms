'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   11 Nov 2022

    
    An implementation of finding the LCM of two numbers. Time Complexity ~O(log(a + b))

'''


def gcd(a, b):
    if a < 0:
        a = -a
    if b == 0:
        return a
    else:
        return gcd(b, a % b)


def lcm(a, b):
    lcm = (a//gcd(a, b))*b
    if lcm > 0:
        return lcm
    else:
        return -lcm


print(lcm(12, 18))  # 36
print(lcm(-12, 18))  # 36
print(lcm(12, -18))  # 36
print(lcm(-12, -18))  # 36
