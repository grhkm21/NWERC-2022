#!/usr/bin/env python3
import math

h, w = map(int, input().split())

b = [input() for _ in range(h)]

dp = [[0] * (w + 1) for _ in range(h + 1)]
for i in range(1, h + 1):
    for j in range(1, w + 1):
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
        if b[i - 1][j - 1] == "O":
            dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1)
            if i > 1 and b[i - 2][j - 1] == "O":
                dp[i][j] = max(dp[i][j], dp[i - 2][j - 1] + 2)
            if j > 1 and b[i - 1][j - 2] == "O":
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 2] + 2)
print(10*((w + h) - (dp[h][w]) * (1 - math.pi / 4)))
