#!/usr/bin/python3
r=[*open(0)]
n,p,k=map(int,r[:3])
a=[(int(x),int(y))for x,y in zip(r[3].split(),r[4].split())]
a.sort()
s=[0]*(9**6)
o=0
for x,y in a:
 if p>=x and s[y]-k:s[y]+=1;o+=1;p-=x
print(o)
