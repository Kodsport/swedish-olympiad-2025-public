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

sortInp =  int(cmdlinearg('sorted', 0))
maxK = int(cmdlinearg('maxK', 19))
minK = int(cmdlinearg('minK', 0))

mode = cmdlinearg('mode', "solveable")

n = 1<<random.randint(minK, maxK)

org = []

cnts = []
tempN = n
while tempN:
    cnts.append((tempN+1)//2)
    tempN //= 2
for i in range(len(cnts)):
    org += [i]*cnts[i]

print(n)
if mode == "solveable":
    random.shuffle(org)
    if sortInp:
        org.sort()
    print(*org)
elif mode == "almost":
    for _ in range(random.randint(1,n)):
        i,j = random.randint(0,n-1),random.randint(0,n-1)

        move = random.randint(min(1,org[i]),org[i])
        org[i] -= move
        org[j] += move
    if sortInp:
        org.sort()
    print(*org)
elif mode == "random":
    if sortInp:
        org.sort()
    print(*[random.randint(0,math.floor(math.log2(n))) for _ in range(n)])
elif mode == "zeros":
    print(*[0]*n)
else:
    assert(mode != mode)




