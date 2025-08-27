#!/usr/bin/python3

n = int(input())
p = int(input())
k = int(input())
costs = [int(i) for i in input().split()]
categories = [int(i) for i in input().split()]

items = [(costs[i], categories[i]) for i in range(n)]
items.sort(key=lambda x: x[0])
ans = 0
taken = {}

for i in range(n):
    item = items[i]
    if not item[1] in taken:
        taken[item[1]] = 0
    if p >= item[0] and taken[item[1]] + 1 <= k:
        taken[item[1]] += 1
        p -= item[0]
        ans += 1

print(ans)
