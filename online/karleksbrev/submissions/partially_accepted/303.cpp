#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
//#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) ((x + y - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

mt19937 rng((random_device())());
template<typename T, typename U> inline int randint(T lo, U hi) { return uniform_int_distribution<int>((int)lo, (int)hi)(rng); } // [lo,hi]

#include "karleksbrev.h"

const int n = 100;

string encode(string x)
{
    string ret = x+"1"+x+"1"+x;
    return ret;
}

string decode(string x)
{
    int bit1 = x[n] == '1';
    int bit2 = x[2 * n + 1] == '1';
    vector<string> parts(3);
    rep(i, 3)
    {
        rep(j, n)
        {
            parts[i].push_back(x.back());
            x.pop_back();
        }
        reverse(all(parts[i]));
        x.pop_back();
    }
    reverse(all(parts));
    if (bit1&&bit2) // take most common one
    {
        map<string, int> occs;
        rep(i, 3) occs[parts[i]]++;
        repe(v, occs) if (v.second == 2) return v.first;
        assert(0);
    }
    else if (bit1&&!bit2)
    {
        return parts[0];
    }
    else if (!bit1&&bit2)
    {
        return parts[2];
    }
    else
    {
        string ret(parts[1]);
        rep(i, n)
        {
            if (ret[i] == '1') ret[i] = '0';
            else ret[i] = '1';
        }
        return ret;
    }
}
