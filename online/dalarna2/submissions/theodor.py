#!/usr/bin/python3


# Denna lösning är bara AI översatt från theodor.cpp
import sys

sys.setrecursionlimit(int(2e5))
from collections import defaultdict

n = int(sys.stdin.readline())
p = list(map(int, sys.stdin.readline().split()))
adj = [[] for _ in range(n)]
for _ in range(n - 1):
    from_node, to_node = map(int, sys.stdin.readline().split())
    from_node -= 1
    to_node -= 1
    adj[from_node].append(to_node)
    adj[to_node].append(from_node)

needed = [0] * n

def dfs(u, last=-1):
    res = needed[u]
    for v in adj[u]:
        if v == last:
            continue
        res += dfs(v, u)
    needed[u] = max(res, p[u])
    return needed[u]

def dfs2(u, passing=0, last=-1):
    ans = 0
    sum_needed = 0
    heavyEdge = (0, -1)
    for v in adj[u]:
        if v == last:
            continue
        sum_needed += needed[v]
        if needed[v] > heavyEdge[0]:
            heavyEdge = (needed[v], v)
    sum_remaining = sum_needed - heavyEdge[0]
    if sum_remaining + passing >= heavyEdge[0]:
        ans = abs(passing - heavyEdge[0])
        sum_remaining -= ans
        ans += min(heavyEdge[0], passing)
        if sum_remaining > 0:
            ans += sum_remaining // 2 + sum_remaining % 2
        return max(ans, p[u])
    else:
        new_passing = max(passing + sum_remaining, p[u])
        return dfs2(heavyEdge[1], new_passing, u)

dfs(0)
result = dfs2(0)
print(result)
