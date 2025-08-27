#!/usr/bin/python3
MOD = int(1e9 + 7)

dp = []
n, k, s, a = map(int, input().split())

def count(i, blasts_left, k):
    if i == n:
        return 1

    # Reference for dp
    if dp[i][blasts_left] != -1:
        return dp[i][blasts_left]

    ret = 0

    # Calculate global damage
    global_damage = k * a
    # Monsters with health [0, global_damage] are already dead
    ret += global_damage * count(i + 1, blasts_left, k)
    ret %= MOD

    for new_blasts in range(1, k + 1):
        if blasts_left - new_blasts < 0:
            break
        ret += s * count(i + 1, blasts_left - new_blasts, k)
        ret %= MOD

    dp[i][blasts_left] = ret
    return ret

def F(k):
    global dp
    dp = [[-1 for _ in range(350)] for _ in range(350)]
    return count(0, k, k)

ans = (F(k) - F(k-1)) % MOD
print((ans + MOD) % MOD)
