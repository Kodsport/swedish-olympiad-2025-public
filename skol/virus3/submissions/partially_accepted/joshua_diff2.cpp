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

    string f, h;
    cin >> f >> h;

    rep(i, sz(h))
    {
        string c(h);
        c.erase(c.begin() + i);
        if (c==f)
        {
            cout << "Ja";
            return 0;
        }
        rep(j, sz(c))
        {
            string c2(c);
            c2.erase(c2.begin() + j);
            if (c2 == f)
            {
                cout << "Ja";
                return 0;
            }
        }
    }
    cout << "Nej";

    return 0;
}
