#!/usr/bin/env python3
a,b = [int(i) for i in input().split('/')]
d = int(a/b)

n = int(2*a/b+1)
t = sum(range(n))

e = [(i+1,i+2) for i in range(n-1)]

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
        print(n,len(e))
        for i in e:
            print(*i)
        break
