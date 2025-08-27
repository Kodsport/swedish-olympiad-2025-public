#!/usr/bin/python3

s = input()
t = input()
r = 0
for c in s:
    while r < len(t) and t[r] != c:
        r += 1
    if r == len(t):
        print("nej")
        exit()
    r += 1
print("ja")
