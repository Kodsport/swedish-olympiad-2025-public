#!/usr/bin/python3

s = input()
t = 0
h = 0

for c in s:
    if c == 'T':
        t += 1
    else:
        h += 1
    if max(t,h) >= 11 and abs(t-h) >= 2:
        t = 0
        h = 0

print(f"{t}-{h}")
