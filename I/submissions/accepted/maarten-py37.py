#!/usr/bin/env python3
from functools import reduce
print(*(999999 if t not in l else reduce(__import__("math").gcd, (s + i for i, x in enumerate(l.split()) if t in x))
        for s, l in [(int(input().split()[0]), input())] for t in "FB"))
