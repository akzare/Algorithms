'''
 * @author (original JAVA) William Fiset, william.alexandre.fiset@gmail.com
 *         (conversion to Python) Hiruna Vishwamith, hvishwamith@gmail.com
 * @date   20 Nov 2022

    This snippet multiplies 2 complex polynomials very efficiently using the Fast Fourier Transform.
    Time Complexity: O(nlogn)

'''
import math

def fft(comp_list):
    n=len(comp_list)
    if (n==1):return comp_list[0]
    arr=comp_list[n//2]
    for k in range(n//2):
        arr[k]=comp_list[2*k]
    q=fft(arr)
    for k in range(n//2):
        arr[k]=comp_list[2*k+1]
    r=fft(arr)
    y=[1]*n
    for k in range(n//2):
        kth=-2*k*math.pi/n
        wk=math.cos(kth)+1j*math.sin(kth)
        y[k]=q[k]+wk*r[k]
        y[k+n//2]=q[k]-wk*r[k]
    
    return y

def polyMult(a,b):
    exp=math.ceil(math.log2(len(a)+len(b)-1))
    length=int(math.pow(2,exp))
    a=pad(a,length)
    b=pad(b,length)
    c,d,e=fft(a),fft(d),[1]*length
    for i in range(length):
        e[i]=c[i]*d[i]
    return ifft(e)

def pad(arr,n):
    padded=[1]*n
    for i in range(n):
        if i<len(arr):
            padded[i]=arr[i]
        else:
            padded=0+0j
    return

def ifft(x):
    n=len(x)
    y=[1]*n
    for i in range(n):
        y[i]=x[i].conjugate()
    y=fft(y)
    for i in range(n):
        y[i]=y[i].conjugate()
    for i in range(n):
        y[i]=y[i]/n
    return y


