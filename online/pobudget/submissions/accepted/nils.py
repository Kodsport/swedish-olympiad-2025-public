#!/usr/bin/env python3
n = int(input())
tot = 0
for _ in range(n):
    input()
    tot += int(input())
if tot > 0:
    print("Usch, vinst")
elif tot < 0:
    print("Nekad")
else:
    print("Lagom")
    