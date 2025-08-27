#!/usr/bin/python3
import pulp
# Model: for every pair of nodes (i, j), we have a variable representing number of paths we send
# between i and j. We minimize sum of these. For every node, sum of all paths that go through it
# must be >= p[i]

def solve_dalarna_ilp(n, p, edges):
    tree = [[] for i in range(n)]
    for u, v in edges:
        tree[u].append(v)
        tree[v].append(u)

    prob = pulp.LpProblem("MinimizeDalarna", pulp.LpMinimize)

    num_paths = {}
    for i in range(n):
        for j in range(i + 1, n):
            num_paths[(i, j)] = pulp.LpVariable(f"path_{i}_{j}", lowBound=0, cat="Integer")

    def find_path_nodes(start, end):
        visited = [0 for i in range(n)]
        visited[start] = 1
        parent = {start: None}
        queue = [start]
        while queue:
            node = queue.pop(0)
            if node == end:
                break
            for neighbor in tree[node]:
                if not visited[neighbor]:
                    visited[neighbor] = 1
                    parent[neighbor] = node
                    queue.append(neighbor)
        path = []
        current = end
        while current is not None:
            path.append(current)
            current = parent[current]
        return path

    # For every node: sum of paths that pass through it must be >= p[i]
    for i in range(n):
        flow_through_i = []
        for a in range(n):
            for b in range(a + 1, n):
                if i in find_path_nodes(a, b):
                    flow_through_i.append(num_paths[(a, b)])
        prob += pulp.lpSum(flow_through_i) >= p[i], f"FlowThroughNode_{i}"

    # Minimize total number of paths
    prob += pulp.lpSum(num_paths.values())

    prob.solve(pulp.PULP_CBC_CMD(msg=False))

    # Print solution
    if 0:
        varsdict = {}
        for v in prob.variables():
            varsdict[v.name] = v.varValue
        print(varsdict)
    return int(pulp.value(prob.objective))

n = int(input())
p = [int(i) for i in input().split()]
edges = [[int(i)-1 for i in input().split()] for j in range(n-1)]
print(solve_dalarna_ilp(n, p, edges))
