#!/usr/bin/env python3
n,k = [int(i) for i in input().split()]
graph = [[] for i in range(k)]
for a,b in list(set([tuple(sorted([int(j)-1 for j in input().split()])) for i in range(n)])):
    graph[a].append(b)
    graph[b].append(a)

valid = all([len([j for j in graph[i] if i != j and len(graph[j])>1]) < 3 for i in range(k)])

visited = [len(graph[i])==0 for i in range(k)]
cycle = False
components = 0
for i in range(k):
    if visited[i]: continue
    components += 1
    stack = [(-1,i)]
    while stack:
        p,v = stack.pop()
        if visited[v]:
            cycle = True
            continue
        visited[v] = True
        for w in graph[v]:
            if w not in [v,p]:
                stack.append((v,w))
print("Possible" if valid and (not cycle or components == 1) else "Impossible")
