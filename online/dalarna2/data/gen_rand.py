#!/usr/bin/python3

import sys
import random
import math
from random import randint

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n', 100000))
pmin = int(cmdlinearg('pmin', 0))
pmax = int(cmdlinearg('pmax', 1000000000))

print(n)

print(" ".join(map(str, [randint(pmin, pmax) for _ in range(n)])))

order = [i+1 for i in range(n)]
random.shuffle(order)
output = []
for i in range(n-1):
    if randint(0, 1):
        output.append([order[i+1], order[randint(0, i)]])
    else:
        output.append([order[randint(0, i)], order[i+1]])
random.shuffle(output)
for a, b in output:
    print(a, b)
