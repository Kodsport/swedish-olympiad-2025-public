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

vi code = { 255, 174, 107, 58 };

const int n = 100;

map<int, int> invert;
map<int, int> myplace;

void precomp()
{
    invert = map<int, int>();
    myplace = map<int, int>();
    repe(c, code)
    {
        myplace[c] = sz(myplace);
        invert[c] = c;
        rep(i, 8)
        {
            repp(j, i, 8)
            {
                bitset<8> bset(c);
                repp(k, i, j + 1)
                {
                    bset[k] = !bset[k];
                }
                int v = bset.to_ullong();
                //assert(invert.find(v) == invert.end());
                invert[v] = c;
            }
        }
    }
}

int numblocks = 50;
string encode(string x)
{
    precomp();

    __int128_t v = 0;
    rep(i, n)
    {
        if (x[i] == '1') v += (__int128_t(1) << i);
    }

    string ret;
    rep(i, numblocks)
    {
        int c = code[v % 4];
        v /= 4;
        rep(i, 8)
        {
            if (c & (1 << i)) ret += "1";
            else ret += "0";
        }
    }

    return ret;
}



string decode(string x)
{
    precomp();

    __int128_t t = 0;
    __int128_t m = 1;
    while (sz(x))
    {
        string c = x.substr(0, 8);
        rep(i, 8) x.erase(x.begin());
        __int128_t v = 0;
        rep(i, 8) if (c[i] == '1') v += 1 << i;
        int iv = invert[v];
        __int128_t cv = myplace[iv];
        t += m * cv;
        m *= 4;
    }

    string ret;
    rep(i, n)
    {
        if (t & (__int128_t(1) << i)) ret += "1";
        else ret += "0";
    }

    return ret;
}
