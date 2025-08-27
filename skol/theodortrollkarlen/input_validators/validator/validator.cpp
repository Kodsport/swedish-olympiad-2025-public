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
    ll maxnk = Arg("maxnk");
    ll n = Int(1, maxnk);
    Space();
    ll k = Int(1, maxnk);
    Space();
    ll s = Int(1, Arg("maxs"));
    Space();
    ll a = Int(0, Arg("maxa"));
    Endl();
    Eof();
}

