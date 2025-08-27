#!/usr/bin/python3
#@EXPECTED_GRADES@ AC AC RTE RTE RTE RTE
# Chatgpt c++ -> python
MOD = int(1e9 + 7)

MAXN = 100

# Constants and DP table
n, k, s, a = 0, 0, 0, 0
dp = [[-1] * MAXN for _ in range(MAXN)]

def count(i, blasts_left):
    if i == n:
        return 1

    # Reference to memoized dp value
    if dp[i][blasts_left] != -1:
        return dp[i][blasts_left]

    ret = 0
    global_damage = k * a

    # Monsters with health [0, global_damage] are already dead
    for hp in range(global_damage):
        ret = (ret + count(i + 1, blasts_left)) % MOD

    hp = global_damage + 1
    while True:
        remhp = hp - global_damage
        new_blasts = (remhp - 1) // s + 1
        if blasts_left - new_blasts < 0:
            break
        ret = (ret + count(i + 1, blasts_left - new_blasts)) % MOD
        hp += 1

    dp[i][blasts_left] = ret
    return ret

def main():
    global n, k, s, a, dp
    # Input handling
    n, k, s, a = map(int, input().split())

    # First calculation
    a_result = count(0, k)

    # Second calculation with k decreased
    dp = [[-1] * MAXN for _ in range(MAXN)]
    k -= 1
    b_result = count(0, k)

    # Final result calculation
    result = (a_result - b_result + MOD) % MOD
    print(result)

if __name__ == "__main__":
    main()
