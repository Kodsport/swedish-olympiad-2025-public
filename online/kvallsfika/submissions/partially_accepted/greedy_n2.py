#!/usr/bin/python3
#@EXPECTED_GRADES@ WA TLE TLE TLE AC TLE WA TLE

n = int(input())
p = int(input())
k = int(input())
costs = [int(i) for i in input().split()]
categories = [int(i) for i in input().split()]

for _ in range(n):
    for i in range(n-1):
        if costs[i] > costs[i+1]:
            costs[i],costs[i+1]=costs[i+1],costs[i]

ans = 0

for i in range(n):
    if p >= costs[i]:
        p -= costs[i]
        ans += 1

print(ans)
