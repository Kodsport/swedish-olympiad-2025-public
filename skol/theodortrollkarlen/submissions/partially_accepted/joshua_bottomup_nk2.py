#!/usr/bin/python3
#@EXPECTED_GRADES@ AC AC AC TLE TLE TLE
# Chatgpt c++ -> python
MOD = int(1e9 + 7)

def count_bottomup(n, k, s, a):
    dp = [[0] * (k + 1) for _ in range(n + 1)]
    dp[0][0] = 1

    global_damage = k * a
    for i in range(1, n + 1):
        for j in range(k + 1):
            dp[i][j] += dp[i - 1][j] * global_damage
            dp[i][j] %= MOD

            for l in range(j):
                dp[i][j] += s * dp[i - 1][l]
                dp[i][j] %= MOD

    ret = sum(dp[n][i] for i in range(k + 1))
    return ret % MOD

def main():
    # Use input() for input reading
    n, k, s, a = map(int, input().split())
    a_result = count_bottomup(n, k, s, a)
    k -= 1
    b_result = count_bottomup(n, k, s, a)
    result = (a_result - b_result) % MOD
    print((result + MOD) % MOD)

if __name__ == "__main__":
    main()
