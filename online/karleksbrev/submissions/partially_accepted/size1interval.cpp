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

vvi getpattern(int lgm)
{
    vvi pattern(lgm, vi(1<<lgm));
    rep(i, 1<<lgm)
    {
        rep(j, lgm)
        {
            if (i & (1 << j)) pattern[j][i] = 1;
        }
    }
    return pattern;
}

const int lgm = 7;
int numextra = lgm+3;
string encode(string x)
{
    string ret;
    auto add = [&](char c)
    {
        ret += string(1,'1');
        ret += string(1,c);
    };
    int numones = 0;
    repe(v, x)
    {
        add(v);
        if (v == '1') numones++;
    }
    add((numones%2) ? '1' : '0');
    add((numones%2) ? '1' : '0');
    add((numones%4>1) ? '1' : '0');
    
    int m = 1<<lgm;
    while (sz(x) < m) x.push_back('0');

    vvi pattern = getpattern(lgm);

    rep(i, lgm)
    {
        int parity = 0;
        rep(j, m)
        {
            if (pattern[i][j] && x[j] == '1') parity ^= 1;
        }
        add(parity ? '1' : '0');
    }
    return ret;
}

vi tonum(string x)
{
    vi ret(sz(x));
    rep(i, sz(x)) if (x[i] == '1') ret[i] = 1;
    return ret;
}

string tostring(vi x)
{
    string ret(sz(x), '0');
    rep(i, sz(x)) if (x[i]) ret[i] = '1';
    return ret;
}

string solvesingle(string xx)
{
    vi x = tonum(xx);
    vi parities;
    vi meat;
    repp(i, sz(x) - numextra * 2, sz(x))
    {
        if (i%2==1) parities.push_back(x[i]);
    }
    rep(i, sz(x) - numextra * 2)
    {
        if (i % 2 == 1) meat.push_back(x[i]);
    }
    int parity = 0;
    repe(v, meat) parity ^= v;
    int numagree = (parity == parities[0]) + (parity == parities[1]);
    if (numagree>0) // error in last parity bits
    {
        return tostring(meat);
    }
    else // error in meat
    {
        int m = 1<<lgm;
        vvi pattern = getpattern(lgm);
        int pos = 0;
        rep(mask, lgm)
        {
            int subparity = 0;
            rep(i, sz(meat)) // meat is not padded
            {
                if (pattern[mask][i]) subparity ^= meat[i];
            }
            if (parities[mask + 3] != subparity) pos |= 1 << mask;
        }
        meat[pos] ^= 1;
        return tostring(meat);
    }
    assert(0);
}

string decode(string x)
{
    bool singleerror = 1;
    rep(i, sz(x))
    {
        if (i % 2 == 0) singleerror &= x[i] == '1';
    }
    if (singleerror) return solvesingle(x);
    else
    {
        vi meat;
        rep(i, sz(x) - numextra * 2)
        {
            if (i % 2 == 1) meat.push_back(x[i]=='1');
        }
        return tostring(meat);
    }
}
