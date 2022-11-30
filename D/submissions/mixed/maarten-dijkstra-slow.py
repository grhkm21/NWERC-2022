#!/usr/bin/env python3
# @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
import heapq

(h, w), hpi, oo = map(int, input().split()), __import__("math").pi / 2, 1e18
grid, res = [*(input() + " " for _ in range(h)), " " * (w + 1)], [[0] * (2 * w + 1) for y in range(2 * h + 1)]

pq = [(1, 0, 1), (1, 1, 0)]
while pq:
    d, x, y = heapq.heappop(pq)
    if res[y][x]: continue
    res[y][x] = d
    # Odd row: going direct two spaces down, or right-and-down.
    # Even row: going direct two spaces right, or down-and-right.
    for dd, xx, yy in ((2, x, y + 2) if y & 1 else (2, x + 2, y),
                       (2 if grid[y // 2][x // 2] == "X" else hpi, x + 1, y + 1)):
        if xx > 2 * w or yy > 2 * h or res[yy][xx]: continue
        heapq.heappush(pq, (d + dd, xx, yy))

print(10 * (min(res[-2][-1], res[-1][-2]) / 2 + .5))
