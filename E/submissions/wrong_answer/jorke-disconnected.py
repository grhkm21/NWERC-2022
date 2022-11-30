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
        # print n+1 instead of n so there is one disconnected vertex
        print(n+1,len(e))
        for i in e:
            print(*i)
        break
