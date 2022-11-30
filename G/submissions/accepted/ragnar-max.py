#!/usr/bin/env python3

import random

N = 30
pat = random.choices("01", k=N)

q = 0
read = [input()]
s = 0
while read[-N:] != pat:
    if s < N and read[s] != pat[s]:
        q += 1
        print("? flip", flush=True)
        input()
    s += 1
    q += 1
    print("? right", flush=True)
    read.append(input())
n = s - N + 1

while q < 3 * n + 500:
    q += 1
    print("? flip")

print(f"! {n}")
