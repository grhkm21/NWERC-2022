#!/usr/bin/env python3

(c, d), v = map(int, input().split()), input().split()
f = lambda l: d+1 if sum(l) == 0 else c + l.index(1) if sum(l) <= 1 else l[l.index(1) + 1 :].index(1) + 1
print(f([int('F' in x) for x in v]), f([int('B' in x) for x in v]))
