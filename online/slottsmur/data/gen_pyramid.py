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
# tlo = int(cmdlinearg('tlo', 1)) // man kan ju inte bara ha update
c = int(cmdlinearg('c', 50))

hi = 10**9
extra_w = randint(10, 1000)
print(n,q)
heights_left = [i*extra_w+3 for i in range(1, math.floor(n/2)+1)]
heights_right = [i*extra_w-7 for i in range(1, math.floor((n+1)/2)+1)]


heights_right.reverse()

for x in heights_right:
    heights_left.append(x)

for i in range(10000):
    r = randint(0, n-1)
    heights_left[r] -= randint(0, heights_left[r]-1)

print(*heights_left)

heights = heights_left.copy()

for i in range(q):
    t = random.randint(1, 100)
    if t<=c:
        while True:
            pos = randint(1, n)
            if heights[pos-1] < hi:
                break
        value = 1
        if pos != n:
            value = randint(1, math.floor(1.2*abs(heights[pos]-heights[pos-1])+1))
        value = min(int(1e9)-heights[pos-1], value)
        heights[pos-1] += value
        print(2, pos, value)
    else:
        length = randint(0, n-1)
        start = randint(1, n-length)
        print(1, start, start+length)
