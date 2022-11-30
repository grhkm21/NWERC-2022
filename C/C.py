from math import floor, sqrt


def calc(r2):
    # r2 is square of radius, which is an integer
    # sum top right quadrant then multiply by 4
    s = 0
    x = 1
    while x**2 <= r2:
        s += floor(sqrt(r2 - x**2))
        x += 1
    return s * 4


s = int(input())
l = 0
r = 10**9
res = -1

while r >= l:
    mid = (l + r) // 2
    if calc(mid) > s:
        res = mid
        r = mid - 1
    else:
        l = mid + 1

print(sqrt(res))
