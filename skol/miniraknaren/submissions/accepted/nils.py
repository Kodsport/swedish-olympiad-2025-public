#!/usr/bin/python3
n = int(input())
m = int(input())
ans = 0
while n > 0:
    if m <= n <= 2*m-2:
        ans += 2
        break
    if n%m == 0:
        n //= m
    else:
        n -= n%m
    ans += 1
print(ans)
