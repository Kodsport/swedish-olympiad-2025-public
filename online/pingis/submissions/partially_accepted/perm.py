#!/usr/bin/env python3
#@EXPECTED_GRADES@ AC AC AC TLE TLE TLE TLE

from itertools import permutations
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

def valid(x):
    size = n
    while size > 2:
        size //= 2
        for i in range(0,n,size):
            temp = 0

            for j in range(i,i+size):
                #print(i,j,size)
                temp += a[x[j]-1]
            if temp < size-1: # stämmer det här?
                return False
    return True

for x in permutations([*range(1,n+1)]):
    if valid(x):
        print(*x)
        exit()
