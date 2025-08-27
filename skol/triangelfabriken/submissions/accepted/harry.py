#!/usr/bin/python3

a,b,c = [int(input()) for _ in range(3)]

m = max(a,b,c)

if m > 90:
    print("Trubbig Triangel")
elif m == 90:
    print("Ratvinklig Triangel")
else:
    print("Spetsig Triangel")
