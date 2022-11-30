#!/usr/bin/env python3
import random
random.seed(987)

class UnionFind:
  def __init__(self, n):
    self.par = list(range(n))

  def find(self, a): # path compression
    b = a
    while a != self.par[a]:
      a = self.par[a]
    while b != a:
      self.par[b], b = a, self.par[b]
    return a

  def union(self, a, b):
    a, b = self.find(a), self.find(b)
    if a == b: return False
    a, b = random.sample([a,b], 2)
    self.par[a] = b
    return True

def solve():
  m, n = map(int, input().split())

  adj = [[] for _ in range(n)]
  uf = UnionFind(n)
  for _ in range(m):
    a, b = map(lambda x: int(x)-1, input().split())
    adj[a].append(b)
    adj[b].append(a)
    uf.union(a,b)
  adj = [set(v) for v in adj]

  for a in range(n):
    k = 0
    for b in adj[a]:
      k += b != a and len(adj[b]) > 1
    if k > 2:
      return False

  node_count = [0] * n
  edge_count = [0] * n
  loop_count = [0] * n
  for a in range(n):
    node_count[uf.find(a)] += 1
    for b in adj[a]:
      edge_count[uf.find(a)] += a < b;
      loop_count[uf.find(b)] += a == b;

  singles, chains, circles = 0, 0, 0
  for k in range(n):
    if edge_count[k] + loop_count[k] == 0:
      singles += 1
    elif edge_count[k] < node_count[k]:
      chains += 1
    elif edge_count[k] + loop_count[k] > 0:
      circles += 1

  return circles == 0 or (circles == 1 and chains == 0);

print('possible' if solve() else 'impossible')
