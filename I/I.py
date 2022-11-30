from math import gcd
from functools import reduce

a, b = map(int, input().split())
arr = input().split()
fs, bs = [], []

for i in range(b - a + 1):
    if 'Fizz' in arr[i]:
        fs.append(i + a)
    if 'Buzz' in arr[i]:
        bs.append(i + a)

ft = b + 1 if (len(fs) == 0) else (
    reduce(gcd, [fs[i + 1] - fs[i] for i in range(len(fs) - 1)])
    if len(fs) > 1 else fs[0])

bt = b + 1 if (len(bs) == 0) else (
    reduce(gcd, [bs[i + 1] - bs[i] for i in range(len(bs) - 1)])
    if len(bs) > 1 else bs[0])

print(ft, bt)
