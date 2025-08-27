#!/usr/bin/python3

MOD = 10**9+7
MAXN = 2*10**5+5

def binomial(i, j):
    if i < 0 or j < 0 or i < j:
        return 0
    return (((fac[i]*inv[j])%MOD)*inv[i-j])%MOD

def f(k):
    ans = 0
    p1 = 1
    p2 = pow(s,n,MOD)
    s_inv = pow(s,MOD-2,MOD)
    ka = (k*a)%MOD

    for m in range(n+1):
        temp = (binomial(n, m) * p1)%MOD
        temp *= (binomial(k, n-m) * p2)%MOD
        temp %= MOD
        ans += temp
        p1 = (p1*ka)%MOD
        p2 = (p2*s_inv)%MOD
    return ans

n,k,s,a = map(int,input().split())
fac = [0] * MAXN
inv = [0] * MAXN
t = 1
for i in range(MAXN):
    fac[i] = t
    t *= (i+1)
    t %= MOD
inv[MAXN-1] = pow(fac[MAXN-1], MOD-2, MOD)
for i in range(MAXN-1)[::-1]:
    inv[i] = (inv[i+1] * (i+1))%MOD

print((f(k)-f(k-1))%MOD)
