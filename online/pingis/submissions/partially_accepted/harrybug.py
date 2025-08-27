#!/usr/bin/env python3
#@EXPECTED_GRADES@ AC AC AC WA WA WA WA
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


groups = [[] for _ in range(len(cnts))]
for i,x in enumerate(a):
    groups[x].append(i)

for row in groups:
    row.sort()

tree = [-1]*n

tempN = n
ind = 0
while tempN:
    tempN //= 2
    for i,x in enumerate(groups[ind]):
        tree[i+tempN] = x
    ind += 1


ans = [-1]*n
for i in range(n):
    curr = (n+i)
    size = 1
    
    antal = 0
    best = curr//2
    while curr:
        curr //= 2
        size <<= 1
        remain = size-i%size
        if tree[curr] < 1e9-1:
            antal += 1
        if tree[best] > tree[curr]:
            best = curr
        if antal == remain:
            break
    
    ans[i] = tree[best] + 1
    tree[best] = 1e9


print(*ans)
 
        
