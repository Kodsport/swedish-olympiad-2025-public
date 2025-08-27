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
    int n = Int(1, Arg("maxn"));
    Space();
    int q = Int(1, Arg("maxq"));
    Endl();

    vi h(n);
    h = SpacedInts(n, 1, 1000000000);

    int queryType = Arg("c", 100);
    queryType = (queryType == 0 ? 1 : 2);

    bool onlyUpdate = 1;

    for(int i = 0; i < q; i++){
        int t = Int(1, queryType);
        if(t == 1) onlyUpdate = 0;
        Space();
        if(t == 1){
            int l = Int(1, n);
            Space();
            int r = Int(l, n);  
        }else{
            int idx = Int(1, n);
            Space();

            int max_w = 1000000000 - h[idx - 1];
            assert(max_w >= 1); 
            int w = Int(1, max_w);
            h[idx - 1] += w; 
        }
        Endl();
    }
    assert(!onlyUpdate);
    Eof();
}