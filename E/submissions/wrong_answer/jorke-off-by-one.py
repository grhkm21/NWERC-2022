#!/usr/bin/env python3
a,b = [int(i) for i in input().split('/')]
d = int(a/b + 1)

n = d
t = sum(range(d))

e = [(i+1,i+2) for i in range(d-1)]

while True:
    if a*n < t*b:
        e.append((d-1,n+1))
        n += 1
        t += d-1
        if d == 1:
            print("impossible")
            break
    elif a*n > t*b:
        e.append((d,n+1))
        n += 1
        t += d
    else:
        # Add extra vertices to the correct solution
        while d>1 and n+b <= 10**6:
            x = b*d-a
            y = b-x
            for i in range(x):
                e += [(d-1,n+1)]
                n += 1
            for i in range(y):
                e += [(d,n+1)]
                n += 1
        # Change one vertex such that the average distance is just off
        if d>1:
            e[-1] = (2*d-1 - e[-1][0],e[-1][1])
        # Print output
        print(n,len(e))
        for i in e:
            print(*i)
        break
