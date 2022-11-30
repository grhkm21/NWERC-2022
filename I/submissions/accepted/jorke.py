#!/usr/bin/env python3
import math
(l,h) = [int(i) for i in input().split()]
a = input().split()
f,b = 0,0
for i in range(h-l+1):
    if 'F' in a[i]: f = math.gcd(f,l+i)
    if 'B' in a[i]: b = math.gcd(b,l+i)
print(f if f>0 else h+1, b if b>0 else h+1)
