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
        # Add extra edges that don't matter for the solution
        if n>n_init:
            for i in range(random.randint(1,100000)):
                x = random.randint(n_init+1,n)
                y = random.randint(n_init+1,n)
                e.append((x,y))

        # Randomize vertex and edge ordering
        vertex_permutation = list(range(1,n))
        random.shuffle(vertex_permutation)
        vertex_permutation = [0] + vertex_permutation
        random.shuffle(e)

        # Print output
        print(n,len(e))
        for x,y in e:
            x = vertex_permutation[x-1]+1
            y = vertex_permutation[y-1]+1
            if random.randint(1,2) == 1:
                x,y = y,x
            print(x,y)

        break
