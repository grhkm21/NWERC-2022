#!/usr/bin/env python3

# Using some WolframAlpha magic
# d/dx((1/2 d1 (h - x) (h + x) + (d2 x^2)/2)/(d1 (h - x) + d2 x))
#  = (d1^2 (h - x)^2 - d1 d2 (h^2 - 2 h x + 2 x^2) + d2^2 x^2)/(2 (d1 (h - x) + d2 x)^2) = 0
# x = (2 d1 h ± sqrt(4 d1^2 h^2 - 4 d1 h^2 (d1 - d2)))/(2 (d1 - d2)) (d1!=d2)
# x = (2 * a * h - sqrt(4 * a * a * h * h - 4 * a * h * h * (a - w)))/(2 * (a - w))
print(*((h * (a - (a * w) ** 0.5)) / (a - w) for h, r, a, w in [map(int, input().split())]))
