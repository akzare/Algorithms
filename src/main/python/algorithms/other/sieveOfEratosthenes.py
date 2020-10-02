def SieveOfEratosthenes(n): 
    pr=[True for i in range(n + 1)] 
    primes=2
    while (primes*primes<=n): 
        if (pr[primes]==True): 
            for i in range(primes*2,n+1,primes): 
                pr[i] = False
        primes+=1
    pr[0]= False
    pr[1]= False
    for p in range(n + 1): 
        if pr[p]: 
            print(p)

n = int(input())
SieveOfEratosthenes(n)
