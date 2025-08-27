#!/usr/bin/env python3
#@EXPECTED_GRADES@ AC AC WA WA WA WA WA

# Caseworking for N <= 4

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

if n == 1:
    print(1)
elif n == 2:
    print(1,2)
else:
    if a[:2] == [0,0] or sorted(a[:2]) == [1,2]:
        print(1,3,2,4)
    else:
        print(1,2,3,4)
 
