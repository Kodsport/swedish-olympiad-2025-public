// 2 (N + Hamming code + parity 3 times)
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

vvi getpattern(int lgm)
{
    vvi pattern(lgm, vi(1 << lgm));
    rep(i, 1 << lgm)
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
        ret += string(1, '1');
        ret += string(1, c);
    };
    int numones = 0;
    repe(v, x)
    {
        add(v);
        if (v == '1') numones++;
    }
    add((numones % 2) ? '1' : '0');
    add((numones % 2) ? '1' : '0');
    add((numones % 2) ? '1' : '0');

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
        if (i % 2 == 1) parities.push_back(x[i]);
    }
    rep(i, sz(x) - numextra * 2)
    {
        if (i % 2 == 1) meat.push_back(x[i]);
    }
    int parity = 0;
    repe(v, meat) parity ^= v;
    int numagree = (parity == parities[0]) + (parity == parities[1]);
    if (numagree > 0) // error in last parity bits
    {
        return tostring(meat);
    }
    else // error in meat
    {
        int m = 1;
        int lgm = 0;
        while (m < sz(meat)) m *= 2, lgm++;
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
        int l = -1, r = -1;
        rep(i, sz(x))
        {
            if (i % 2 == 0 && x[i] == '0')
            {
                l = i;
                break;
            }
        }
        assert(l != -1);
        for (int i = sz(x) - 1; i >= 0; i--)
        {
            if (i % 2 == 0 && x[i] == '0')
            {
                r = i;
                break;
            }
        }

        vi meat;
        rep(i, sz(x) - numextra * 2)
        {
            if (i % 2 == 0)
            {
                if (x[i] == '1') meat.push_back(x[i + 1] == '1');
                else
                {
                    if (x[i + 1] == '1') meat.push_back(0);
                    else meat.push_back(1);
                }
            }
        }
        vi parities;
        repp(i, sz(x) - numextra * 2, sz(x))
        {
            if (i % 2 == 0)
            {
                if (x[i] == '1') parities.push_back(x[i + 1] == '1');
                else
                {
                    if (x[i + 1] == '1') parities.push_back(0);
                    else parities.push_back(1);
                }
            }
        }
        assert(sz(parities) == numextra);
        // there are now at most 2 errors in total in parities/meat
        int meatparity = 0;
        repe(v, meat) meatparity ^= v;

        int numones = 0;
        repe(v, meat) numones += v;

        // error spots are l-1 and r+1
        int numleft = 0;
        if (r + 1 < sz(x) - numextra * 2) numleft++;
        if (l - 1 < sz(x) - numextra * 2) numleft++;
        if (numleft == 0) return tostring(meat);
        if (numleft == 1)
        {
            vi occs(2);
            rep(i, 3) occs[parities[i]]++;
            int realparity = (occs[0] > 1 ? 0 : 1);
            if (realparity == meatparity)
            {
                return tostring(meat);
            }
            if (l != 0) meat[l / 2 - 1] ^= 1;
            return tostring(meat);
        }
        // no errors in parity info
        int m = 1;
        int lgm = 0;
        while (m < sz(meat)) m *= 2, lgm++;
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
        if (pos == 0 && parities[0] == meatparity) // no errors
        {
            return tostring(meat);
        }
        if (meatparity != parities[0]) // 1 error
        {
            meat[pos] ^= 1;
            return tostring(meat);
        }
        // 2 errors
        meat[l / 2 - 1] ^= 1;
        meat[r / 2] ^= 1;


        return tostring(meat);
    }
}
