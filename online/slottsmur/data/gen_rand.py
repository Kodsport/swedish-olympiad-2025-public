#!/usr/bin/python3

import sys
import random
import math
from random import randint
from string import ascii_lowercase

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
q = int(cmdlinearg('q'))
c = int(cmdlinearg('c', 50))

hi = 10**9
print(n,q)
heights = [randint(1, hi) for i in range(n)]
print(*heights)

i = 0
while i < q:
    t = randint(1,100)
    if t<=c:
        times = 0
        while True:
            times += 1
            pos = randint(1, n)
            if heights[pos-1] < hi:
                break
            if times > 100:
                break
        if times > 100:
            continue
            
        value = randint(1, hi-heights[pos-1])
        heights[pos-1] += value
        print(2, pos, value)
    else:
        length = randint(0, n-1)
        start = randint(1, n-length)
        print(1, start, start+length)
    i += 1
