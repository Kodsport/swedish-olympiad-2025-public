#include <bits/stdc++.h>
using namespace std;

#include "karleksbrev.h"

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

string encode(string x)
{
    string ret;
    repe(v, x)
    {
        ret += "1";
        ret += v;
    }
    return ret;
}

string decode(string x)
{
    string ret = "";
    for (int i = sz(x)-1; i >= 0; i--)
    {
        if (i % 2 == 0 && x[i] == '0')
        {
            x[i] = '1';
            break;
        }
    }

    rep(i, sz(x))
    {
        if (i % 2 == 0)
        {
            if (x[i] == '0') ret += (x[i + 1] == '1' ? '0' : '1');
            else ret += x[i + 1];
        }
    }
    return ret;
}

