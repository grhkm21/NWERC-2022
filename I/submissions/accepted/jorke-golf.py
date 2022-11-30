#!/usr/bin/env python3
(l, h), a, f = map(int, input().split()), input().split(), lambda x: x[-1] - x[-2]
print(*[f([-h - 1, 0] + [l + i for i, j in enumerate(a) if c in j]) for c in 'FB'])
