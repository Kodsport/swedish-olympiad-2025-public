//@EXPECTED_GRADES@ AC AC AC AC TLE TLE
// O(NK)
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < (high); i++)
#define repp(i, low, high) for (int i = (low); i < (high); i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { cin.tie(0)->sync_with_stdio(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

int dp[2010][2010];
int n, k, s, a;
const int mod = int(1e9 + 7);

int count_bottomup()
{
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    int global_damage = k * a;
    repp(i, 1, n + 1)
    {
        rep(j, k+1)
        {
            dp[i][j] += dp[i - 1][j] * global_damage;
            dp[i][j] %= mod;
        }
        repp(j, 1, k + 1) dp[i - 1][j] = (dp[i - 1][j] + dp[i - 1][j - 1]) % mod;

        repp(j, 1, k + 1)
        {
            dp[i][j] += s * dp[i - 1][j-1];
            dp[i][j] %= mod;
        }
    }

    int ret = 0;
    rep(i, k+1) ret += dp[n][i];
    return ret % mod;
}

signed main()
{
    fast();

    cin >> n >> k >> s >> a;
    int a = count_bottomup();
    k--;
    int b = count_bottomup();
    cout << ((a - b)%mod+mod)%mod;

    return 0;
}
