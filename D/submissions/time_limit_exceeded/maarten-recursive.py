#!/usr/bin/env python3

def dist(x, y):
    if x == 0: return y
    if y == 0: return x

    # Odd row. Going direct down from two spaces up, or right-and-down from the space to the left-and-up.
    if y & 1:
        return min(dist(x, y - 2) + 2 if y > 1 else infinity,
                   dist(x - 1, y - 1) + (2 if grid[y // 2][x // 2 - 1] == "X" else half_pi))
    # Even row. Going direct right from two spaces left, or down-and-right from the space to the left-and-up.
    else:
        return min(dist(x - 2, y) + 2 if x > 1 else infinity,
                   dist(x - 1, y - 1) + (2 if grid[y // 2 - 1][x // 2] == "X" else half_pi))


(h, w), half_pi, infinity = map(int, input().split()), __import__("math").pi / 2, 1e18
grid = [input() for _ in range(h)]
print(10*(min(dist(2 * w, 2 * h - 1), dist(2 * w - 1, 2 * h)) / 2 + .5))
