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
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

vector<string> forbidden;
int ans = 0;
void rec(string& s, int l)
{
    if (sz(s)==l)
    {
        bool good = 1;
        repe(f, forbidden) good &= s.find(f) == string::npos;
        if (good) ans++;
        return;
    }

    repp(c, 'a', 'z' + 1)
    {
        s.push_back(c);
        rec(s, l);
        s.pop_back();
    }
}

signed main()
{
    fast();

    int l, n;
    cin >> l >> n;

    rep(i, n)
    {
        string s;
        cin >> s;
        forbidden.push_back(s);
    }
    string s;
    rec(s, l);
    cout << ans;

    return 0;
}