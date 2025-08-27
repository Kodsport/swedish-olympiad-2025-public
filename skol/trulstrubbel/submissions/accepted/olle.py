#!/usr/bin/python3
s = input()

h, t = 0, 0
for c in s:
    if c == "H":
        h += 1
    else:
        t += 1
    if max(t, h) >= 11 and max(t, h) >= min(t, h) + 2:
        t = 0
        h = 0
print(f"{t}-{h}")