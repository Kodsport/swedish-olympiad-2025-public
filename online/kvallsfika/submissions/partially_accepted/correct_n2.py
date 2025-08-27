#!/usr/bin/python3
#@EXPECTED_GRADES@ AC TLE TLE TLE AC TLE AC TLE

n = int(input())
p = int(input())
k = int(input())
costs = [int(i) for i in input().split()]
categories = [int(i) for i in input().split()]

items = [(costs[i], categories[i]) for i in range(n)]

for _ in range(n):
    for i in range(n-1):
        if costs[i] > costs[i+1]:
            costs[i],costs[i+1]=costs[i+1],costs[i]
            categories[i],categories[i+1]=categories[i+1],categories[i]

ans = 0
taken = {}

for cost, category in zip(costs, categories):
    if not category in taken:
        taken[category] = 0
    if p >= cost and taken[category] + 1 <= k:
        taken[category] += 1
        p -= cost
        ans += 1

print(ans)
