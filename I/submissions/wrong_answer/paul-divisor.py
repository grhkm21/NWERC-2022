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
    return d+1
  if len(xs) == 1:
    return [x for x in range(xs[0]-1,0,-1) if xs[0]%x == 0][0]
  return xs[1]-xs[0]

print(solve(fizzes), solve(buzzes))
