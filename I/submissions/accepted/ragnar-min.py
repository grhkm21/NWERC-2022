#!/usr/bin/env python3

c, d = map(int, input().split())
items = input().split()

fizzes = []
buzzes = []
for i, s in enumerate(items):
  if s[:4] == 'Fizz':
    fizzes.append(c+i)
  if s[-4:]  == 'Buzz':
    buzzes.append(c+i)

def solve(xs):
  if len(xs) == 0:
    for i in range(d-c+2, 10**6+1):
      if (c-1)//i == d//i:
        return i
    assert False
  if len(xs) == 1:
    for i in range((d-c+2)//2, 10**6+1):
      if xs[0]%i == 0 and (c-1)//i+1 == d//i:
        return i
    assert False
  return xs[1]-xs[0]

print(solve(fizzes), solve(buzzes))
