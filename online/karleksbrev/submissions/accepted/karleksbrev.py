#!/usr/bin/python3
mod = 1125899906842679

def hashf(x: str) -> int:
    ret = 0
    for v in x:
        ret = (ret + (1 if v == '1' else 0)) * 2374662 % mod
    return ret

k = 50

def hashstring(x: str) -> str:
    ret = ['0'] * k
    h = hashf(x)
    
    for j in range(k):
        if h & (1 << j):
            ret[j] = '1'

    return ''.join(ret)

def encode(x: str) -> str:
    return x + hashstring(x)

def decode(x: str) -> str:
    n = len(x)
    
    for i in range(n):
        for j in range(i, n):
            u = list(x)
            
            for l in range(i, j + 1):
                u[l] = '0' if u[l] == '1' else '1'
            
            meat = ''.join(u[:n - k])
            encoded = encode(meat)
            
            if ''.join(u) == encoded:
                return meat
    
    raise AssertionError("its joever")
