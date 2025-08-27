#!/usr/bin/python3
n, s, a = map(int, input().split())
life = [int(i) for i in input().split()]

def any_alive(life):
    return any(i > 0 for i in life)

ans = 0
while any_alive(life):
    for i in range(n):
        life[i] -= a
    most_life = 0
    for i in range(n):
        if life[i] > life[most_life]:
            most_life = i
    life[most_life] -= s
    ans += 1
print(ans)