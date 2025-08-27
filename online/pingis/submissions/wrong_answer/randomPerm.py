#!/usr/bin/env python3
import random
n = int(input())

a = [*range(1,n+1)]

random.shuffle(a)
print(*a)
