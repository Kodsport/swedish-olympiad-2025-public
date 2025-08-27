//@EXPECTED_GRADES@ AC WA WA WA WA WA
// O(NSK^2), has overflow issues
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
// create monsters in weakly increasing order of health
int count(int i, int blasts_left)
{
    if (i == n)
    {        
        return 1;
    }

    int& v = dp[i][blasts_left];
    if (v != -1) return v;

    int ret = 0;

    int global_damage = k * a;
    // monsters with health [0, global_damage] are already dead
    repp(hp, 1, global_damage + 1)
    {
        ret += count(i + 1, blasts_left);
    }
    int hp = global_damage + 1;
    while (true)
    {
        int remhp = hp - global_damage;
        int new_blasts = (remhp - 1) / (s) + 1;
        if (blasts_left - new_blasts < 0) break;
        ret += count(i + 1, blasts_left - new_blasts);

        ret %= mod;
        hp++;
    }


    return v = ret;
}

signed main()
{
    fast();

    memset(dp, -1, sizeof(dp));
    cin >> n >> k >> s >> a;
    int a = count(0, k);
    memset(dp, -1, sizeof(dp));
    k--;
    int b = count(0, k);
    cout << a-b;

    return 0;
}
