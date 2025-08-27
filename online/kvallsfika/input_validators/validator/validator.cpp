#include "validator.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


void run() {
    int n = Int(0, Arg("maxn", int(1e5)));
    Endl();
    int p = Int(1, int(1e8));
    Endl();
    int k = Int(1, n);
    Endl();
    int max_c = min((int)Arg("maxc", p), p);
    vi costs = SpacedInts(n, 1, max_c);
    SpacedInts(n, 1, int(1e5));

    if (Arg("buyall", 0))
    {
        assert(accumulate(all(costs), 0LL) <= p);
    }
    if (Arg("nocategories", 0)) assert(k==n);

    Eof();
}

