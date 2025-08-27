#!/usr/bin/python3
#@EXPECTED_GRADES@ WA AC WA WA AC AC WA WA

n = int(input())
p = int(input())
k = int(input())
costs = [int(i) for i in input().split()]
categories = [int(i) for i in input().split()]
costs.sort()
ans = 0

for i in range(n):
    if p >= costs[i]:
        p -= costs[i]
        ans += 1

print(ans)
