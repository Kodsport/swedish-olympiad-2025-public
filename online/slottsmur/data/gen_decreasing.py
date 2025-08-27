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
c = int(cmdlinearg('c',50))

reverse = int(cmdlinearg('rev',0))

hi = 10**9
print(n,q)

if not reverse:

    heights = [10**8+i+randint(0, 3) for i in range(n)]
    heights[0] = 2*10**8
    print(*heights)

    r = (n-1)//2+1

    for i in range(q):
        t = randint(1,100)
        if t<=c:
            pos = randint(1, n)
            
            value = randint(1, 5)
            heights[pos-1] -= value
            print(2, pos, value)
        else:
            print(1, 1, r)
            r = min(r+1, n)
else:
    heights = [10**8+n-i+randint(0, 3) for i in range(n)]
    heights[-1] = 2*10**8
    print(*heights)

    r = (n-1)//2+1

    for i in range(q):
        t = randint(1,100)
        if t<=c:
            pos = randint(1, n)
            
            value = randint(1, 5)
            heights[pos-1] -= value
            print(2, pos, value)
        else:
            print(1, r, n)
            r = max(r-1, 1)