#!/usr/bin/env python3
import math

l, r = map(int, input().split())
x = input().split()
a = 0
b = 0
for i, s in enumerate(x):
  if s[0] == 'F':
    a = math.gcd(a,i+l)
  if s[-4:][0]  == 'B':
    b = math.gcd(b,i+l)
if a == 0:
  a = r+1
if b == 0:
  b = r+1
print(a, b)
