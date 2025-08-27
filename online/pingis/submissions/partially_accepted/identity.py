#!/usr/bin/env python3
from collections import Counter

n = int(input())
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
else:
    print(*range(1,n+1))
