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
p = int(cmdlinearg('pmax', 1000000000))
amountStars = int(cmdlinearg('amountStars', 1))
partStar = float(cmdlinearg('partStar', 1.0))

print(n)

print(" ".join(map(str, [randint(0, p) for _ in range(n)])))

order = [i+1 for i in range(n)]
random.shuffle(order)
output = []
amNodesInStars  = max(1, int(partStar*n))
amountStars = min(amountStars, amNodesInStars)
amNodesPerStar = amNodesInStars//amountStars
for i in range(amountStars):
    for j in range(amNodesPerStar):
        if j > 0:
            output.append([order[i*amNodesPerStar+j], order[i*amNodesPerStar]])
        elif i != 0:
            output.append([order[i*amNodesPerStar+random.randint(0, amNodesPerStar-1)], order[(i-1)*amNodesPerStar+random.randint(0, amNodesPerStar-1)]])
        
for i in range(max(0, amountStars*amNodesPerStar-1), n-1):
    if randint(0, 1):
        output.append([order[random.randint(0, i)], order[i+1]])
    else:
        output.append([order[i+1], order[random.randint(0, i)]])
random.shuffle(output)
for a, b in output:
    print(a, b)
