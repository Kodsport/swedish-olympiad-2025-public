#!/usr/bin/python3

m=max(int(input())for _ in "abc")
s="Ratvinklig"
if m>90:
    s="Trubbig"
if m<90:
    s="Spetsig"
print(s,"Triangel")
