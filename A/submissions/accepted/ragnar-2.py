#!/usr/bin/env python3

# Translation of ragnar-2.cpp

# (zeros in interval, ones in interval, best cut inside interval)
def op(l, r): return (l[0] + r[0], l[1] + r[1], max(l[2]+r[0], r[2]+l[1]));
_id = (0,0,0)


n = int(input()) + 1

v = list(map(int, input().split()))
o = list(range(n))
o.sort(key=lambda i: v[i])
tree = [(0,1,1) for _ in range(2*n)]
for i in range(n-1, -1, -1): tree[i] = op(tree[2*i], tree[2*i+1])
def update(i):
    tree[i+n] = (1, 0, 1)
    i = (i+n)//2
    while i > 0:
        tree[i] = op(tree[2*i], tree[2*i+1])
        i //= 2
def query(l, r):
    lhs = rhs = _id
    l += n
    r += n
    while l < r:
        if l&1:
            lhs = op(lhs, tree[l])
            l += 1
        if not (r&1):
            rhs = op(tree[r], rhs)
            r -= 1

        l //= 2
        r //= 2
    return op(op(lhs, tree[l]) if l==r  else lhs, rhs)

left_one = 0
right_zero = -1
ans = 0

for i in range(n):
    pos = o[i]
    right_zero=max(right_zero, pos)
    while left_one < n and v[left_one] <= v[pos]: left_one += 1
    update(pos)
    m = query(left_one, right_zero)[2]
    if (m+i)%2!=1 : m -= 1
    ans = max(ans, m)

print(ans)

