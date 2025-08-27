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


signed main()
{
    fast();

    int n;
    cin >> n;
    string t = to_string(n);
    int dsum = 0;
    repe(c, t) dsum += c - '0';
    auto good = [&](int i)
        {
            string s = to_string(i);
            if (sz(s) != sz(t)) return false;
            int n_dsum = 0;
            repe(c, s) n_dsum += c - '0';
            return n_dsum == dsum;
        };
    
    string lo, hi;


    rep(i, int(1e6))
    {
        if (good(i))
        {
            lo = to_string(i);
            break;
        }
    }
    
    for (int i = int(1e6); i >= 0; i--)
    {
        if (good(i))
        {
            hi = to_string(i);
            break;
        }
    }

    cout << lo << " " << hi;

    return 0;
}
