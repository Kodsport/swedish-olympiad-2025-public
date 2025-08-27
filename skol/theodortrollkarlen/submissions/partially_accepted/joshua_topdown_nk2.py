#!/usr/bin/python3
#@EXPECTED_GRADES@ AC AC AC RTE RTE RTE
# Chatgpt c++ -> python
MOD = int(1e9 + 7)

MAXN = 501

n = k = s = a = 0  # These will be set later based on input.
dp = [[-1] * MAXN for _ in range(MAXN)]

def count(i, blasts_left):
    if i == n:
        return 1

    if dp[i][blasts_left] != -1:
        return dp[i][blasts_left]

    ret = 0
    global_damage = k * a
    # Monsters with health [0, global_damage] are already dead
    ret += global_damage * count(i + 1, blasts_left)
    ret %= MOD

    for new_blasts in range(1, k + 1):
        if blasts_left - new_blasts < 0:
            break
        ret += s * count(i + 1, blasts_left - new_blasts)
        ret %= MOD

    dp[i][blasts_left] = ret
    return ret

def main():
    global n, k, s, a
    n,k,s,a = [int(i) for i in input().split()]

    # First call to count with full k
    result_a = count(0, k)
    
    # Reset dp and reduce k by 1
    for i in range(MAXN):
        for j in range(MAXN):
            dp[i][j] = -1
    k -= 1
    result_b = count(0, k)
    
    # Output the result with the modulus operation as in the original code
    print(((result_a - result_b) % MOD + MOD) % MOD)

if __name__ == "__main__":
    main()
