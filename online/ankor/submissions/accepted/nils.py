#!/usr/bin/python3

import math
import random


def proj_dist(x2, y2, x1, y1):
    r2 = x2*x2+y2*y2
    dot = x1*x2 + y1*y2
    x_proj = (dot/r2) * x2
    y_proj = (dot/r2) * y2
    sig = 1
    if x1*y2-x2*y1 < 0:
        sig = -1
    return sig * ((x_proj - x1)**2 + (y_proj - y1)**2)**0.5

n = int(input())
n *= 2
P = []
for _ in range(n):
    x, y = map(int, input().split())
    P.append((x+1, y))

k = random.random()

PI = []
for i in range(n):
    PI.append((proj_dist(1, k, P[i][0], P[i][1]), i))
PI.sort()

i = PI[n//2][1]
j = PI[n//2-1][1]

m1 = P[i][1] - k*P[i][0]
m2 = P[j][1] - k*P[j][0]

print(k, (m1+m2)/2 + k)

