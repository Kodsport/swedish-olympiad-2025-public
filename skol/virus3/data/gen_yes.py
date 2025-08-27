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
maxlen = int(cmdlinearg('maxlen', 32))
diff = int(cmdlinearg('diff', 32))
unique = int(cmdlinearg('unique'))

n = random.randint(1, maxlen)
if diff == -1:
    m = random.randint(n, maxlen)
else:
    m = n + diff

chars = [i for i in ascii_lowercase] + ["."]

a = ""
for i in range(n):
    pos = random.randrange(0,len(chars))
    a += chars[pos]
    if unique:
        chars.pop(pos)
    
b = [c for c in a]
if not unique:
    chars = [chr(i) for i in range(ord('a'), ord('z')+1)] + ["."]
while len(b) < m:
    pos = random.randrange(0,len(chars))
    p = random.randint(0, len(b))  # len(my_list) includes the option to append at the end
    b.insert(p, chars[pos])
    if unique:
        chars.pop(pos)

print(a)
print("".join(b))