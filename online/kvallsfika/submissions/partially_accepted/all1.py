#!/usr/bin/python3
#@EXPECTED_GRADES@ WA AC AC AC WA WA WA WA

n = int(input())
p = int(input())
k = int(input())
costs = [int(i) for i in input().split()]
categories = [int(i) for i in input().split()]

ans = 0
taken = [0 for i in range(int(1e5+10))]

for i in range(n):
    if p > 0 and taken[categories[i]] + 1 <= k:
        taken[categories[i]] += 1
        ans += 1
        p -= 1

print(ans)