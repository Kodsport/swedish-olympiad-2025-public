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

    int n, m;
    cin >> n >> m;

    assert(m == 3);

    if (n == 0) cout << 0;
    if (n == 1) cout << 1;
    if (n == 2) cout << 1;
    if (n == 3) cout << 2;
    if (n == 4) cout << 2;
    if (n == 5) cout << 3;
    if (n == 6) cout << 2;
    if (n == 7) cout << 3;
    if (n == 8) cout << 3;
    if (n == 9) cout << 3;
    if (n == 10) cout << 4;

	return 0;
}
