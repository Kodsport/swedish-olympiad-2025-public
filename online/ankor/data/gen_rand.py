#!/usr/bin/python3

import sys
import random
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

n = int(cmdlinearg('n', 1))
mode = cmdlinearg('mode', "random")
x_max = int(cmdlinearg('xmax', int(1e6)))
y_max = int(cmdlinearg('ymax', int(1e6)))
force_x = int(cmdlinearg('x', -1))

points = set()

def generate_point():
    if force_x != -1:
        x = force_x
    else:
        x = random.randint(0, x_max)
    y = random.randint(0, y_max)
    return (x, y)


if mode == "random":
    while len(points) < 2*n:
        point = generate_point()
        points.add(point)

   
points = list(points)

print(n)
for x, y in points:
    print(x, y)




