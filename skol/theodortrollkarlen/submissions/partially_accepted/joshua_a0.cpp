//@EXPECTED_GRADES@ AC AC WA WA WA WA
// O(NSK^2), only works for A=0
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

int dp[1010][1010];
int n, k, s, a;
const int mod = int(1e9 + 7);
int count(int i, int blasts)
{
    if (blasts > k) return 0;
    if (i==n)
    {
        return blasts ==k;
    }

    int& v = dp[i][blasts];
    if (v != -1) return v;

    int ret = 0;

    int hp = 1;
    while (true)
    {
        int new_blasts = (hp-1) / s + 1;
        if (blasts + new_blasts > k) break;
        ret += count(i + 1, blasts + new_blasts);
        
        ret %= mod;
        hp++;
    }


    return v=ret;
}

signed main()
{
    fast();

    memset(dp, -1, sizeof(dp));
    cin >> n >> k >> s >> a;
    cout << count(0, 0);

    return 0;
}
