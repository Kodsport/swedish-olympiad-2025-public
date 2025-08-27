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
maxh = int(cmdlinearg('maxh', 1000000000))
s = int(cmdlinearg('sets', random.randint(1, 1+maxh//10)))
seta = int(cmdlinearg('seta', -1))
# maxh = 1000
# seta = -1

n = random.randint(8, 10)
a = random.randint(1, 30)
if seta != -1: a = seta

print(n, s, a)
print(" ".join([str(random.randint(1, maxh)) for _ in range(n)]))