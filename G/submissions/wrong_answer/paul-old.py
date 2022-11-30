#!/usr/bin/env python3
import sys

def query(s):
  print('? %s' % s)
  sys.stdout.flush()
  return int(input())

x = int(input())
for _ in range(1000):
  if x == 1:
    x = query('flip')
  x = query('right')

x = query('flip')
res = 0
while True:
  res += 1
  x = query('right')
  if x: break

print('! %d' % res)
