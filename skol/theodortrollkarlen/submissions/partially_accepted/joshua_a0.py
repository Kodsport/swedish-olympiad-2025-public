#!/usr/bin/python3
MOD = int(1e9 + 7)

dp = [[-1 for _ in range(100)] for _ in range(100)]
def count(i, blasts):
    if blasts > k:
        return 0
    if i == n:
        return 1 if blasts == k else 0

    if dp[i][blasts] != -1:
        return dp[i][blasts]

    ret = 0
    hp = 1
    while True:
        new_blasts = (hp - 1) // s + 1
        if blasts + new_blasts > k:
            break
        ret += count(i + 1, blasts + new_blasts)
        ret %= MOD
        hp += 1

    dp[i][blasts] = ret
    return ret
    
n, k, s, a = map(int, input().split())

print(count(0, 0))
