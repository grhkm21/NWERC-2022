#!/usr/bin/env python3

import random
import sys

pi = 31415926535897932
pat = [c for c in f"{pi:b}"]
N = len(pat)

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
