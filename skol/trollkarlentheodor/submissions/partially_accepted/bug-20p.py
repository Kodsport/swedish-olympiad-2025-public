#!/usr/bin/python3

#bug: did not mulitply m with dmgall on line 18.

n, dmgone, dmgall = map(int,input().split())
a = [*map(int,input().split())]

if dmgall == 0:
  print(sum((x+dmgone-1)//dmgone for x in a))
  exit()

#binärsök över antal drag
l = 0
r = sum(a)
while l<r:
  
  m = (l+r)//2
  cnt = sum((max(0,x-m)+dmgone-1)//dmgone for x in a)
  if cnt > m:
    l = m+1
  else:
    r = m

print(l)
