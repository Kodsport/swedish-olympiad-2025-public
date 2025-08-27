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
s = randint(1, int(1e5)//2-10)
p = randint(s*2+1, int(1e5))
a = int(cmdlinearg("a"))
b = int(cmdlinearg("b"))

print(s)
print(p)
print(a)
print(b)
