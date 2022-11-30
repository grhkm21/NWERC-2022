#!/usr/bin/env python3

def add_edge(a, b, c): adj[a].append(len(e)), e.append([b, c]), adj[b].append(len(e)), e.append([a, 0])


def dfs(i, cap, delta):
    if i == t: return cap
    if mark[i]: return 0
    mark[i] = True
    for j in adj[i]:
        if (e[j][1] >= delta) and (c := dfs(e[j][0], min(cap, e[j][1]), delta)):
            e[j][1], e[j ^ 1][1] = e[j][1] - c, e[j ^ 1][1] + c
            return c
    return 0


def max_flow():
    global mark
    flow, delta = 0, oo
    while delta > 0:
        mark, c = [False] * N, dfs(s, oo, delta)
        if c > 0: flow += c
        else: delta /= 2
    return flow


(m, n), oo = map(int, input().split()), 0x3f3f3f3f3f3f3f3f
min_count, max_count, mask, N = [0] * 26, [n] * 26, [(1 << 26) - 1] * n, n + 29

for _ in range(m - 1):
    (s, t), count, has_black = input().split(), [0] * 26, [False] * 26

    for i in range(n):
        k = ord(s[i]) - ord('a')
        if t[i] == 'G': mask[i], count[k] = mask[i] & (1 << k), count[k] + 1
        elif t[i] == 'Y': mask[i], count[k] = mask[i] & ~(1 << k), count[k] + 1
        else: mask[i], has_black[k] = mask[i] & ~(1 << k), has_black[k] + 1

    for k in range(26):
        min_count[k] = max(min_count[k], count[k])
        if has_black[k]: max_count[k] = count[k]

s, t, u, mark, adj, e, rem, res = N - 3, N - 2, N - 1, [False] * N, [[] for _ in range(N)], [], n, [ord('a')] * n
for k in range(26):
    _, _, rem = add_edge(s, n + k, min_count[k]), add_edge(u, n + k, max_count[k] - min_count[k]), rem - min_count[k]
add_edge(s, u, rem)
for i in range(n):
    for k in range(26):
        if mask[i] & (1 << k): add_edge(n + k, i, 1)
    add_edge(i, t, 1)

if max_flow() < n:
    print("impossible")
else:
    for i in range(n):
        for j in adj[i]:
            if e[j][1]: res[i] += e[j][0] - n
    print("".join(chr(c) for c in res))
