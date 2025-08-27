#include "validator.h"

#include <bits/stdc++.h>
using namespace std;

#define fo(i, n) for(ll i=0;i<((ll)n);i++)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;



void run() {
    ll n = Int(1, 10);
    Space();
    ll s = Int(1, (ll)1e9);
    Space();
    ll a = Int(0, Arg("maxa", 1e9));
    Endl();

    SpacedInts(n, 0, (int)Arg("maxh", 1e9));
    
    Eof();
}

