#!/usr/bin/env python3
import random

b = int(input())

def query(c):
  global b
  print('?', c)
  b = int(input())

read = []
written = []
k = 16
mask = 12345
for i in range(k):
  nb = (mask >> i) & 1
  read.append(b)
  written.append(nb)
  if b != nb:
    query('flip')
  query('right')

while True:
  read.append(b)
  if read[-k:] == written:
    print('!', len(read)-len(written))
    break
  query('right')
