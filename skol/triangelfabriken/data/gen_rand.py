#!/usr/bin/python3

import sys
import random
import math

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
mode = cmdlinearg('a',"Rand")


if mode == "Trubbig":
    a = random.randint(91,178)
    b = random.randint(1,179-a)
    c = 180-b-a
elif mode == "Ratvinklig":
    a = 90
    b = random.randint(1,179-a)
    c = 180-b-a
elif mode == "Spetsig": #jag tror det här funkar?
    a = random.randint(1,89)
    b = min(89,random.randint(91-a,179-a))
    c = 180-b-a
elif mode == "Rand":
    a = random.randint(1,179)
    b = random.randint(1,179-a)
    c = 180-b-a
else:
    assert 0, "bad argument"

arr = [a,b,c]
random.shuffle(arr)
print("\n".join(map(str,arr)))
