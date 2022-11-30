#!/usr/bin/env python3
n = int(input()) + 1
v = list(map(int, input().split()))
if v == sorted(v):
    print(0)
    exit()
if n%2 == 1:
    v.append(10**9+1)
    n += 1
# do 1 step
v = [x for p in zip(v[0::2], v[1::2]) for x in sorted(p)]
#print(v)
# compute distances
def dist(p):
    t, s = p
    #print(s,t)
    if s == t: return 0
    if t <= s:
        return s-t if s%2==0 else s-t+1
    else:
        return t-s if s%2==1 else t-s+1


print(1+max(map(dist, enumerate(sorted(range(n), key=lambda i: v[i])))))
