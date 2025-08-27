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
n = int(cmdlinearg("n", int(1e5)))
k = int(cmdlinearg("k"))
maxcost = int(cmdlinearg("maxcost", 500))
costs = [randint(1, maxcost) for i in range(n)]
num_categories = int(cmdlinearg("num_categories"))
categories = [randint(1, num_categories) for i in range(n)]

print(n)
print(sum(costs)+1+randint(1, 20))
print(k)
print(*costs)
print(*categories)
