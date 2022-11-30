#!/usr/bin/env python3
n = int(input()) + 1
v = list(map(int, input().split()))
ans = 0
for x in v:
    bits = [y > x for y in v]
    left_ones = 0
    right_zeros = bits.count(False)
    for i, b in enumerate(bits):
        if b:
            left_ones += 1
        else:
            right_zeros -= 1
        if left_ones > 0 and right_zeros > 0:
            ans = max(ans, left_ones + right_zeros - (i + 1) % 2)

print(ans)
