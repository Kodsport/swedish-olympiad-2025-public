#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)

inline void fast() { ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

signed main()
{
    fast();

    int n, q;
    cin >> n >> q;
    vi heights(n);
    rep(i, n) cin >> heights[i];

    while (q--)
    {
        int t;
        cin >> t;
        if (t == 2)
        {
            int i, v;
            cin >> i >> v;
            i--;
            heights[i] += v;
        }
        else
        {
            int l, r;
            cin >> l >> r;
            l--; r--;

            vi l_hi(n, -1);
            vi r_hi(n, -1);

            int lp = -1;
            repp(i, l, r + 1)
            {
                l_hi[i] = lp;
                lp = max(lp, heights[i]);
            }
            int rp = -1;
            for (int i = r; i >= l; i--)
            {
                r_hi[i] = rp;
                rp = max(rp, heights[i]);
            }

            int ans = 0;
            repp(i, l, r + 1)
            {
                int lim = min(l_hi[i], r_hi[i]);
                if (lim > heights[i])
                {
                    ans += lim - heights[i];
                }
            }
            cout << ans << "\n";
        }
    }

    return 0;
}