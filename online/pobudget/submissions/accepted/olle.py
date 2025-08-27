#!/usr/bin/python3

n = int(input())
arr = [input() for i in range(2*n)]
s = sum(int(arr[i]) for i in range(1, 2*n, 2))
if s < 0:
    print("Nekad")
elif s == 0:
    print("Lagom")
else:
    print("Usch, vinst")
