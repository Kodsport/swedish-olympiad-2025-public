#!/usr/bin/env python3
s,p,a,b=[int(input()) for i in range(4)]
ans = 1000000000000000

for j in range(int(1e5)):
    if (s + j) * 2 > p + j:
        ans = min(ans, j * b)
    else:
        i = (p - 2 * s - j) // 2 + 1
        ans = min(ans, i * a + j * b)

print(ans)
