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


pref = cmdlinearg('pref',chr(random.randint(ord("a"),ord("z"))))

rev = int(cmdlinearg("rev", 0))

saveSuff = int(cmdlinearg("save",2))

seen = set()
print(n, m)


size = n-saveSuff

prefix = (pref*n)[:size]

while len(seen) < m:
    
    seen.add(prefix + "".join([chr(random.randint(ord("a"), ord("z"))) for _ in range(random.randint(0,saveSuff))]))



words = list(seen)
random.shuffle(words)

for word in words:
    if rev:
        print(word[::-1])
    else:
        print(word)
    