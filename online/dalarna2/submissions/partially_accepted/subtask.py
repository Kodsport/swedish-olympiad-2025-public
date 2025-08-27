#!/usr/bin/python3

n = int(input())
p = [*map(int,input().split())]

graph = [[] for _ in range(n)]
for _ in range(n-1):
    a,b = map(int,input().split())
    a-=1;b-=1;
    graph[a].append(b)
    graph[b].append(a)


ans = 0
for i,x in enumerate(graph):
    if len(x) == 1:
        ans += p[i]


print((ans+1)//2)