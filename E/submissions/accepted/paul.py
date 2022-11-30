#!/usr/bin/env python3
from fractions import Fraction

goal = Fraction(input())

for n in range(2,10**6):
  if n%goal.denominator != 0 or goal < Fraction(n-1,n) or Fraction(n-1,2) < goal:
    continue

  print(n, n-1)
  d, p, total = 1, 1, 0
  for a in range(2,n+1):
    print(p, a)
    total += Fraction(d,n)
    if total + Fraction((d+1)*(n-a), n) <= goal:
      d += 1
      p = a
  break
else:
  print('impossible')
