#!/usr/bin/env python3
from collections import Counter
import math
n = int(math.log2(int(input())))

wins = [[] for _ in range(n+1)]
ind = list(map(int, input().split()))

# Check if a solution exists:
cnts = []
tempN = 2**n
while tempN:
    cnts.append((tempN+1)//2)
    tempN //= 2
correct = Counter()
for i in range(len(cnts)):
    correct[i] += cnts[i]
if Counter(ind) != correct:
    print(-1)
    exit()

for i in range(2**n):
    wins[ind[i]].append(i)
for i in range(n+1):
    wins[i].sort()
losers = [0]*(2**(n+3))
for i in range(n):
    for j in range(2**i):
        losers[2**i + j] = wins[n-i-1][j]
def solve(node, val):
    if node >= 2**n:
        losers[node] = val
        return
    solve (2*node, min(val, losers[node]))
    solve(2*node+1, max(val, losers[node]))
    return
solve(1, wins[n][0])

for i in range(2**n):
    print(losers[2**n+i] +1 , end = " ")
print()
