#!/usr/bin/env python3
S = int(input())
P = int(input())
A = int(input())
B = int(input())
print(min(A*((P+2)//2-S), B*(P-2*S+1), B+A*(((P+3)//2-S-1))))
