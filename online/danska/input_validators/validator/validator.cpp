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
    int n = Int(1, Arg("nmax", 100));
    Space();
    int m = Int(Arg("mmin", 0), Arg("mmax", 150));
    Endl();

    set<string> seen;
    fo(i, m){
        string s = Line();
        seen.insert(s);
        assert(s.length()<=n&&s.length()>0);
        for(auto &c : s){
            assert(c>='a'&&c<='z');
        }
    }
    assert(seen.size() == m);

    Eof();
}

