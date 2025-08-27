#!/usr/bin/python3
import heapq

n,dmgone,dmgall = map(int,input().split())

a = [*map(lambda x: -int(x),input().split())]

heapq.heapify(a)

temp = 0
out = 0
while a[0] < temp:
    t = heapq.heappop(a)
    t += dmgone
    temp -= dmgall
    out += 1
    heapq.heappush(a,t)

print(out)