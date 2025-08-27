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
    int parity = 0;
    repe(v, x)
    {
        ret += "1";
        ret += v;
        if (v == '1') parity ^= 1;
    }
    ret += "1";
    ret += (parity ? "1" : "0");
    return ret;
}

string decode(string x)
{
    int r = -1;
    for (int i = sz(x)-1;i>=0;i--)
    {
        if (i % 2 == 0 && x[i] == '0')
        {
            r = i;
            break;
        }
    }
    string ret;
    
    rep(i, sz(x)-2)
    {
        if (i % 2 == 0)
        {
            if (x[i] == '0') ret += (x[i + 1] == '1' ? '0' : '1');
            else ret += x[i + 1];
        }
    }
    if (r!=sz(x)-2)
    {
        int realparity = x.back() == '1';
        int parity = 0;
        rep(i, sz(ret))
        {
            if (ret[i] == '1') parity ^= 1;
        }
        if (parity!=realparity)
        {
            int ind = r / 2;
            if (ret[ind] == '1') ret[ind] = '0';
            else ret[ind] = '1';
        }
    }
    
    return ret;
}

