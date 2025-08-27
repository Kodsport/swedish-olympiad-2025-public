#!/usr/bin/python3

n, s, a = map(int, input().split())
h = list(map(int, input().split()))
lo = 0
hi = n*10**9
while lo < hi-1:
    mid = (lo+hi) // 2
    need = 0
    for x in h:
        need += (max(0, x-mid*a)+s-1) // s
    if need <= mid:
        hi = mid
    else:
        lo = mid
print(hi)
