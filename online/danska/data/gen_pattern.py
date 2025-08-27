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


pat = cmdlinearg('pattern',chr(random.randint(ord("a"),ord("z"))))
seen = set()
print(n, m)

l = 1
s = 0


while len(seen) < m:
    while l*len(pat)+s <= n:
        seen.add(pat*l + pat[:s])
        
        s += 1
        if s == len(pat):
            l += 1
            s = 0

        break
    else:
        pat = [chr(random.randint(ord("a"),ord("z"))) for _ in range(random.randint(1,(n+3)//4))]
        pat = "".join(pat)
        l = 1
        s = 0
        continue


words = list(seen)
random.shuffle(words)

for word in words:
    print(word)
    