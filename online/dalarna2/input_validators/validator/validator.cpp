#include "validator.h"

#include <bits/stdc++.h>
using namespace std;

#define fo(i, n) for(ll i=0;i<((ll)n);i++)
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<ll> vl;
typedef vector<vl> vvl;

vvl adj;
vl seen;

bool isTree(int u, int last = -1){
    if(seen[u]) return 0;
    seen[u] = 1;
    for(auto v : adj[u]){
        if(v == last)continue;
        if(!isTree(v, u)) return 0;
    }
    return 1;
}

void run() {
    int n = Int(1, Arg("nmax", 100000));
    Endl();
    ll pmin = Arg("pmin", 0);
    ll pmax = Arg("pmax", 1000000000);
    fo(i, n){
        if(i > 0)Space();
        Int(pmin, pmax);
    }
    Endl();

    adj.assign(n, vl());
    seen.assign(n, 0);
    fo(i, n-1){
        int a = Int(1, n);
        Space();
        int b = Int(1, n);
        adj[--a].pb(--b);
        adj[b].pb(a);
        Endl();
    }
    assert(isTree(0));
    fo(i, n) assert(seen[i]);
    if(Arg("line", 0))fo(i, n) assert(adj[i].size() <= 2);

    Eof();
}

