// Four russian+independent bitvectors, found using clique solver
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

vi code = { 1980, 1961, 1821, 1438, 474, 850, 351, 961, 397, 923, 1491, 1349, 764, 745,
            203, 1240, 1167, 134, 584, 1543, 1034, 1684, 1742, 16 };

map<int, int> invert;
map<int, int> myplace;
const int n = 100;
void precomp()
{
    invert = map<int, int>();
    myplace = map<int, int>();
    repe(c, code)
    {
        myplace[c] = sz(myplace);
        invert[c] = c;
        rep(i, 11)
        {
            repp(j, i, 11)
            {
                bitset<11> bset(c);
                repp(k, i, j + 1)
                {
                    bset[k] = !bset[k];
                }
                int v = bset.to_ullong();
                assert(invert.find(v) == invert.end());
                invert[v] = c;
            }
        }
    }
}

int numblocks = 22;
string encode(string x)
{
    precomp();

    __int128_t v = 0;
    rep(i, n)
    {
        if (x[i] == '1') v += (__int128_t(1) << i);
    }

    string ret;
    //cout << "v: " << v << "\n";
    rep(i, numblocks)
    {
        int c = code[v % 24];
        //cout << "c: " << c << ", v%24: " << (v%24) << "\n";
        //cout << "c,b: ";
        v /= 24;
        rep(i, 11)
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
        string c = x.substr(0, 11);
        rep(i, 11) x.erase(x.begin());
        __int128_t v = 0;
        rep(i, 11) if (c[i] == '1') v += 1 << i;
        int iv = invert[v];
        __int128_t cv = myplace[iv];
        t += m * cv;
        m *= 24;
    }

    string ret;
    rep(i, n)
    {
        if (t & (__int128_t(1) << i)) ret += "1";
        else ret += "0";
    }

    return ret;
}
