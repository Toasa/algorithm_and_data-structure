import math

def eratosthenes(n):
    limit = math.sqrt(n)
    primes = []
    data = [ i+1 for i in range(1, n) ]

    while True:
        p = data[0]
        if p >= limit:
            return primes + data
        primes.append(p)
        data = [ d for d in data if d % p != 0 ]

primes_to1000 = eratosthenes(1000000)
print(len(primes_to1000))
