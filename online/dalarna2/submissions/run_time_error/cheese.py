#!/usr/bin/python3

# Cheese solution that should not work on non-line-graphs O(np**2)

import sys
sys.setrecursionlimit(3*10**6)

n = int(input())
p = [*map(int,input().split())]

edges = [[] for _ in range(n)]
for _ in range(n-1):
    a,b = map(lambda x: int(x)-1, input().split())
    edges[a].append(b)
    edges[b].append(a)

children = [[] for _ in range(n)]
visited = [0]*n
visited[0] = 1
BFS = [0]
for cur in BFS:
    for nei in edges[cur]:
        if visited[nei]:
            continue

        visited[nei] = 1
        BFS.append(nei)

start = BFS[-1]
visited = [0]*n
visited[start] = 1
BFS = [start]
for cur in BFS:
    for nei in edges[cur]:
        if visited[nei]:
            continue

        visited[nei] = 1
        children[cur].append(nei)
        BFS.append(nei)


maxP = max(p)

children.append([start])

for row in children:
    row.sort(key = lambda x:-p[x])

                
memo = [[-1]*(maxP+1) for _ in range(n+2)]
def dp(ind, kid, remains):
    if kid == len(children[ind]):
        return 0

    
    if memo[children[ind][kid]][remains] != -1:
        return memo[children[ind][kid]][remains]
    

    best = 1e9

    for use in range(0,maxP+1):
        if use <= remains:
            best = min(best,dp(children[ind][kid],0,max(p[children[ind][kid]],use)) 
                            + dp(ind,kid+1,remains-use) 
                            + max(p[children[ind][kid]]-use,0))
        else:
            best = min(best,dp(children[ind][kid],0,max(p[children[ind][kid]]-use,0))    
                            + dp(ind,kid+1,use-remains) 
                            + use-remains 
                            + max(p[children[ind][kid]]-use,0))
    
    memo[children[ind][kid]][remains] = best
    return best

    
print(dp(n,0,0))
    