#!/usr/bin/env python3

# Translation of ragnar-2.cpp, golfed by Maarten

# (zeros in interval, ones in interval, best cut inside interval)
def op(l, r): return (l[0] + r[0], l[1] + r[1], max(l[2] + r[0], r[2] + l[1]));


n, _id, left_one, right_zero, ans = int(input()) + 1, (0, 0, 0), 0, -1, 0
v, o, tree = list(map(int, input().split())), list(range(n)), [(0, 1, 1) for _ in range(2 * n)]
o.sort(key=lambda i: v[i])
for i in range(n - 1, -1, -1): tree[i] = op(tree[2 * i], tree[2 * i + 1])


def update(i):
    tree[i + n], i = (1, 0, 1), (i + n) // 2
    while i > 0: tree[i], i = op(tree[2 * i], tree[2 * i + 1]), i // 2


def query(l, r):
    lhs = rhs = _id
    l, r = l + n, r + n
    while l < r:
        if l & 1: lhs, l = op(lhs, tree[l]), l + 1
        if not (r & 1): rhs, r = op(tree[r], rhs), r - 1
        l, r = l // 2, r // 2
    return op(op(lhs, tree[l]) if l == r else lhs, rhs)


for i in range(n):
    pos = o[i]
    right_zero = max(right_zero, pos)
    while left_one < n and v[left_one] <= v[pos]: left_one += 1
    update(pos)
    if ((m := query(left_one, right_zero)[2]) + i) % 2 != 1: m -= 1
    ans = max(ans, m)

print(ans)
