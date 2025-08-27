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

seed = int(cmdlinearg('seed', sys.argv[-1]))
random.seed(seed)
n = 100
k = int(cmdlinearg("k"))

print(n, k)
mode = cmdlinearg("mode")
if mode=="random":
    print(0, seed)
elif mode=="size1":
    print(1, seed)
elif mode=="evenends":
    print(2, seed)
elif mode=="lefteven":
    print(3, seed)
else:
    assert 0, "No mode provided"
