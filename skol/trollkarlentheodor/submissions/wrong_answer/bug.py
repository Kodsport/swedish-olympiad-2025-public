#!/usr/bin/python3
# bug: rounding down


n, dmgone, dmgall = map(int,input().split())
a = [*map(int,input().split())]

if dmgall == 0:
  print(sum(x//dmgone for x in a))
  exit()

#binärsök över antal drag
l = 0
r = sum(a)
while l<r:
  m = (l+r)//2
  cnt = sum(max(0,x-m)//dmgone for x in a)
  if cnt > m:
    l = m+1
  else:
    r = m
print(l)
