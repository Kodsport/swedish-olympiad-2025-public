#!/usr/bin/env python3
#@EXPECTED_GRADES@ WA WA WA WA WA AC WA

from collections import Counter

n = int(input())

assert(bin(n).count("1") == 1)

a = [*map(int,input().split())]


# Check if a solution exists:
cnts = []

tempN = n
while tempN:
    cnts.append((tempN+1)//2)
    tempN //= 2

correct = Counter()
for i in range(len(cnts)):
    correct[i] += cnts[i]

if Counter(a) != correct:
    print(-1)
    exit()

ans = [0]*n
inc = 2
curr = 1
for i in range(n):
    if ans[i] == 0:
        for j in range(i,n,inc):
            ans[j] = curr
            curr += 1
        inc *= 2
print(*ans)



