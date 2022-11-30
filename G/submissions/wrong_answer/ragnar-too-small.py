#!/usr/bin/env python3

import random

N = 15
random.seed(31415)
pat = random.choices("01", k=N)

read = [input()]
s = 0
while read[-N:] != pat:
    if s < N and read[s] != pat[s]:
        print("? flip", flush=True)
        input()
    s += 1
    print("? right", flush=True)
    read.append(input())

print(f"! {s-N+1}")
