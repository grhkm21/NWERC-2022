#!/usr/bin/env python3
import random
a,b = [int(i) for i in input().split('/')]

# Compute a solution
d = int(a/b)
n = int(2*a/b+1)
t = sum(range(n))
e = [(i+1,i+2) for i in range(n-1)]

n_init = n

while True:
    if a*n < t*b:
        e.append((d,n+1))
        n += 1
        t += d
        if d == 0:
            print("impossible")
            break
    elif a*n > t*b:
        e.append((d+1,n+1))
        n += 1
        t += d+1
    else:
        # Increase the total amount of edges to 10^6
        e *= 1000000//len(e)
        while len(e) <= 1000000:
            e.append(random.choice(e))

        # Print output
        print(n,len(e))
        for x,y in e:
            print(x,y)
        break
