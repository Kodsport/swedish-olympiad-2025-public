#!/usr/bin/python3

s = input()

t = h = 0
for x in s:
    if x == "T":
        t += 1
    elif x == "H":
        h += 1
    
    if (t >= 11 or h >= 11):
        t = h = 0

print(f"{t}-{h}")
