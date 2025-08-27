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
n = int(cmdlinearg("n"))
k = int(cmdlinearg("k"))
mc = int(cmdlinearg("maxcost"))
costs = [randint(1, mc) for i in range(n)]
num_categories = int(cmdlinearg("num_categories"))
categories = [randint(1, num_categories) for i in range(n)]

print(n)
print(min(int(1e8), randint(1, sum(costs))))
print(k)
print(*costs)
print(*categories)
