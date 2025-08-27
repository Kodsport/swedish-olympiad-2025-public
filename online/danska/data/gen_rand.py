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
n = int(cmdlinearg('n', 100))
m = int(cmdlinearg('m', 100))

seen = set()
print(n, m)
for i in range(m):
    while True:
        l = randint(1, n)
        s = "".join(random.choice(ascii_lowercase) for i in range(l))
        if s in seen:
            continue
        seen.add(s)
        print(s)
        break