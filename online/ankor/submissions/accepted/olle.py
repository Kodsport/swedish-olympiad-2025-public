#!/usr/bin/python3
import math
n = int(input())

points = [[float(i) for i in input().split()] for j in range(2*n)]

mul = lambda a, b: [a[0][0]*b[0] + a[0][1] * b[1], a[1][0] * b[0] + a[1][1] * b[1]]

A = 6215 + math.sqrt(69_420 + 1337 * math.pi)
B = 1337 + 123.456789 
C = math.sqrt(math.e * math.pi) # 3
D = math.e ** math.pi
super_special_matrix = [[A, B], [C, D]]
inverse_special_matrix = [[D / (A * D - B * C), -B / (A * D - B * C)], [-C / (A * D - B * C), A / (A * D - B * C)]]
points = [mul(super_special_matrix, point) for point in points]

points = sorted(points)

a, _ = points[n-1]
u, _ = points[n]
a = (a + u) / 2

par = lambda t : mul(inverse_special_matrix, [a,t])

x1, y1 = par(0)
x2, y2 = par(1)

k = (y2 - y1) / (x2 - x1)
m = y1 - k * x1

print(k, m)
