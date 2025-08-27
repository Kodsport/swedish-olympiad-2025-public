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


for i in range(q):
    t = randint(1, 100)
    if t <= c:
        while True:
            pos = randint(1, n)
            if heights[pos-1] < hi:
                break
        value = randint(1, hi-heights[pos-1])
        heights[pos-1] += value
        print(2, pos, value)
    else:
        is_max = randint(1, 2)
        length = randint(math.floor(n/1.5), n-1)

        if is_max == 1:
            length = n-randint(1, 14)

        start = randint(1, n-length)
        print(1, start, start+length)
