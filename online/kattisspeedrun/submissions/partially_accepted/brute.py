#!/usr/bin/env python3
s,p,a,b=[int(input()) for i in range(4)]

ans = 100000000000

for i in range(1000):
    for j in range(1000):
        if (s + i + j) * 2 > p + j:
            ans = min(ans, i * a + j * b)

print(ans)
