#!/usr/bin/python3

n, dmgone, dmgall = map(int,input().split())
a = [*map(int,input().split())]

#binärsök över antal drag
l = 0
r = sum(a)
while l<r:
  
  m = (l+r)//2
  cnt = sum((max(0,x-m*dmgall)+dmgone-1)//dmgone for x in a)
  if cnt > m:
    l = m+1
  else:
    r = m

print(l)
