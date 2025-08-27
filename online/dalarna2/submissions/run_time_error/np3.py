#!/usr/bin/python3

# This should get WA for non-line cases O(np**3)

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


                
memo = [[[-1]*(maxP+1) for _ in range((maxP+1))] for _ in range(n+2)]

def dp(ind, kid, remains, krav):
    if kid == len(children[ind]):
        return int(1e9)*(krav != 0)

    
    if memo[children[ind][kid]][remains][krav] != -1:
        return memo[children[ind][kid]][remains][krav]
    

    best = 1e9

    for use in range(0,maxP+1):
        #print(use,ind,kid,remains,krav)
        if use <= remains:
            best = min(best,dp(children[ind][kid],0,use, max(0,p[children[ind][kid]]-use)) 
                            + dp(ind,kid+1,remains-use,krav))
        else:
            best = min(best,dp(children[ind][kid],0,use, p[children[ind][kid]]-use)    
                            + dp(ind,kid+1,use-remains,max(krav-(use-remains),0)) 
                            + use-remains)
    
    memo[children[ind][kid]][remains][krav] = best
    return best

    
print(dp(n,0,0,0))
    