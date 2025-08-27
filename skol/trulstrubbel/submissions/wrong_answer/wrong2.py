#!/usr/bin/python3

s = input()

t = s.count("T")%11
h = s.count("H")%11

print(f"{t}-{h}")
