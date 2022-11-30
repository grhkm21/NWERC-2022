#!/usr/bin/env python3
from collections import namedtuple, deque

Edge = namedtuple('Edge', ['to', 'f', 'c'])

class MaxFlow:
  def __init__(self, n):
    self.adjlist = [[] for _ in range(n)]
    self.edges = []

  def addEdge(self, source, target, c):
    self.adjlist[source].append(len(self.edges))
    self.edges.append(Edge(target, 0, c))
    self.adjlist[target].append(len(self.edges))
    self.edges.append(Edge(source, 0, 0))

  def bfs(self, lim):
    self.dist = [-1 for _ in range(len(self.adjlist))]
    self.dist[self.t] = len(self.adjlist) + 1
    q = deque()
    q.append(self.t)
    while q and self.dist[self.s] < 0:
      cur = q.popleft()
      for idx in self.adjlist[cur]:
        to = self.edges[idx].to
        if self.dist[to] < 0 and self.edges[idx ^ 1].c - self.edges[idx ^ 1].f >= lim:
          self.dist[to] = self.dist[cur] - 1
          q.append(to)
    return self.dist[self.s] >= 0

  def dfs(self, v, flow):
    if flow == 0:
      return False
    if v == self.t:
      return True
    while self.pt[v] < len(self.adjlist[v]):
      idx = self.adjlist[v][self.pt[v]]
      to = self.edges[idx].to
      if self.dist[to] == self.dist[v] + 1 and self.edges[idx].c - self.edges[idx].f >= flow:
        if self.dfs(to, flow):
          self.edges[idx] = self.edges[idx]._replace(f=self.edges[idx].f + flow)
          self.edges[idx ^ 1] = self.edges[idx ^ 1]._replace(f=self.edges[idx ^ 1].f - flow)
          return True
      self.pt[v] = self.pt[v] + 1
    return False

  def maxFlow(self, source, target):
    self.s = source
    self.t = target
    self.dist = [0 for _ in range(len(self.adjlist))]
    lim = 1 << 8
    flow = 0
    while lim >= 1:
      if not self.bfs(lim):
        lim //= 2
        continue
      self.pt = [0 for _ in range(len(self.adjlist))]
      while self.dfs(self.s, lim):
        flow += lim
    return flow

m, n = map(int, input().split())
m = m - 1

forced = [[False for _ in range(n)] for _ in range(26)]
forbidden = [[False for _ in range(n)] for _ in range(26)]
lo = [0 for _ in range(26)]
hi = [n for _ in range(26)]

for q in range(m):
  s, t = input().split()

  gy = [0 for _ in range(26)]
  b = [False for _ in range(26)]

  for i in range(n):
    l = ord(s[i]) - ord('a')
    if t[i] == 'G':
      gy[l] = gy[l] + 1
      forced[l][i] = True
    elif t[i] == 'Y':
      gy[l] = gy[l] + 1
      forbidden[l][i] = True
    else:
      b[l] = True
      forbidden[l][i] = True

  for l in range(26):
    lo[l] = max(lo[l], gy[l])
    if b[l]:
      hi[l] = min(hi[l], gy[l])

ans = ['0' for _ in range(n)]

slack = n

for i in range(n):
  for l in range(26):
    if forced[l][i]:
      ans[i] = chr(l + ord('a'))
      lo[l] = max(lo[l] - 1, 0)
      hi[l] = hi[l] - 1
      slack = slack - 1

slack = slack - sum(lo)

maxflow = MaxFlow(n + 29)

source = n + 26
auxsource = source + 1
target = source + 2

maxflow.addEdge(source, auxsource, slack)
for i in range(n):
  maxflow.addEdge(i + 26, target, 1)

for l in range(26):
  maxflow.addEdge(source, l, lo[l])
  maxflow.addEdge(auxsource, l, hi[l] - lo[l])

for i in range(n):
  if ans[i] != '0':
    continue
  for l in range(26):
    if forbidden[l][i]:
      continue
    maxflow.addEdge(l, i + 26, 1)

maxflow.maxFlow(source, target)

for i in range(n):
  for idx in maxflow.adjlist[i + 26]:
    e = maxflow.edges[idx]
    if e.to < 26 and e.f != 0:
      ans[i] = chr(e.to + ord('a'))

print(''.join(ans))
