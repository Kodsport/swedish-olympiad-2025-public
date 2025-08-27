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

int dp[40][40];
string f, h;
int lcs(int i, int j)
{
    if (i == sz(f) || j == sz(h)) return 0;
    
    int& v = dp[i][j];
    if (v != -1) return v;
    v = 0;

    v = max(v, lcs(i + 1, j));
    v = max(v, lcs(i, j + 1));
    if (f[i] == h[j]) v = max(v, 1 + lcs(i + 1, j + 1));

    return v;
}

signed main()
{
    fast();

    memset(dp, -1, sizeof(dp));
    cin >> f >> h;
    cout << (lcs(0, 0) == sz(f) ? "Ja" : "Nej");

    return 0;
}
