//@EXPECTED_GRADES@ AC TLE TLE TLE TLE TLE
// O(answer*poly(N,K,S,A))
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

int n, k, s, a;
int count(int i, int blasts_left)
{
    if (i == n)
    {
        return 1;
    }
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
        hp++;
    }


    return ret;
}

signed main()
{
    fast();

    cin >> n >> k >> s >> a;
    int a = count(0, k);
    k--;
    int b = count(0, k);
    cout << a-b;

    return 0;
}
