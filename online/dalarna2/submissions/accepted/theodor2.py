#!/usr/bin/python3

# Denna lösning använder iterativ DFS istället för rekursion. AI från theodor.py


from collections import defaultdict


n = int(input())
p = list(map(int, input().split()))
adj = [[] for _ in range(n)]
for _ in range(n - 1):
    from_node, to_node = map(int, input().split())
    from_node -= 1
    to_node -= 1
    adj[from_node].append(to_node)
    adj[to_node].append(from_node)

needed = [0] * n

# Iterative version of dfs
def dfs_iterative(start):
    stack = [(start, -1)]  # Stack holds (current node, parent)
    post_order_stack = []  # To simulate post-order processing
    while stack:
        u, parent = stack.pop()
        post_order_stack.append((u, parent))  # Add to post-order stack for processing
        for v in adj[u]:
            if v != parent:
                stack.append((v, u))

    # Post-order processing (mimics recursion unwinding)
    while post_order_stack:
        u, parent = post_order_stack.pop()
        res = needed[u]
        for v in adj[u]:
            if v != parent:
                res += needed[v]
        needed[u] = max(res, p[u])

# Iterative version of dfs2
def dfs2_iterative(start):
    stack = [(start, 0, -1)]  # Stack holds (current node, passing value, parent)
    result = 0

    while stack:
        u, passing, parent = stack.pop()
        sum_needed = 0
        heavy_edge = (0, -1)

        # Calculate sum_needed and find the heavy edge
        for v in adj[u]:
            if v == parent:
                continue
            sum_needed += needed[v]
            if needed[v] > heavy_edge[0]:
                heavy_edge = (needed[v], v)

        sum_remaining = sum_needed - heavy_edge[0]

        if sum_remaining + passing >= heavy_edge[0]:
            ans = abs(passing - heavy_edge[0])
            sum_remaining -= ans
            ans += min(heavy_edge[0], passing)
            if sum_remaining > 0:
                ans += sum_remaining // 2 + sum_remaining % 2
            result = max(result, max(ans, p[u]))
        else:
            new_passing = max(passing + sum_remaining, p[u])
            stack.append((heavy_edge[1], new_passing, u))

    return result

dfs_iterative(0)
result = dfs2_iterative(0)
print(result)
