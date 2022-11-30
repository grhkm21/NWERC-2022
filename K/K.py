import sys

sys.setrecursionlimit(10**6)


def main():
    n, k = map(int, input().split())

    # build graph, check if
    # (1) only single loop or (multiple) paths after removing leaves
    # (2) degree <= 2
    # note that we check every component

    graph = {i: set() for i in range(k)}
    for _ in range(n):
        a, b = map(int, input().split())

        graph[a - 1].add(b - 1)
        graph[b - 1].add(a - 1)

    graph = {v: list(graph[v]) for v in graph}

    # degree
    for v in range(k):
        # leaves `u` are fine, since (on the pizza) we can just place it
        # next to `v` and ignore them
        if len([u for u in graph[v] if u != v and graph[u] != [v]]) > 2:
            # print(graph)
            return False

    # search on each nodes for components
    vis = [False] * k
    cycle = False
    cnt = 0

    # update: dfs will segfault and run out of stack
    '''
    def dfs(v, pt=-1):
        # pt is parent i.e. previous node
        # l is length, ignores "fake cycles"
        # returns cycle or not

        # handle cycles
        if vis[v]:
            return True

        # search
        vis[v] = True
        _cycle = False
        for u in graph[v]:
            if u != pt and u != v:
                _cycle = _cycle | dfs(u, v)

        return _cycle
    '''

    for v in range(k):
        if vis[v] or graph[v] == []:
            continue

        cnt += 1
        # print(f'dfs({v})')

        # simulates dfs
        stack = [(v, -1)]
        while len(stack) > 0:
            v, pt = stack.pop()
            if vis[v]:
                cycle = True
                continue

            vis[v] = True
            for u in graph[v]:
                if u != pt and u != v:
                    stack.append((u, v))

    if cycle:
        return cnt == 1

    return True


if __name__ == '__main__':
    if main():
        print("possible")
    else:
        print("impossible")
