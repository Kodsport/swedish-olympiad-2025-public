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
int count(int i, int taken)
{
    if (taken > k) return 0;
    if (i==n)
    {
        return taken==k;
    }

    int& v = dp[i][taken];
    if (v != -1) return v;

    int ret = 0;

    int hp = 1;
    while (true)
    {
        if (hp<=k*a)
        {
            // either it is killed by splash damage
            ret += count(i + 1, taken);
            // or we blast it once (this seems wrong?)
            ret += count(i + 1, taken+1);
        }
        else
        {
            int remhp = hp - k * a;
            int num_takes = remhp / s + 1;
            if (taken + num_takes > k) break;
            ret += count(i + 1, taken + num_takes);
        }
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
