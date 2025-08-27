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
    string F = Line();
    string H = Line();

    ll n=F.size();
    ll m=H.size();
    assert(n<=m);
    assert(n >= 1 && n <= 32);
    assert(m >= 1 && m <= 32);
    ll max=Arg("diff");
    if (max!=-1) assert(m-n==max);

    bool unique=Arg("unique");

    auto check = [&](string s)
    {
        if(unique) {
            vector<bool> seen(200,false);
            for (auto c : s) {
                assert(seen[c]==false);
                seen[c]=true;
            }
        }
        for (auto c : s) {
            assert(c=='.' || (c >= 'a' && c <= 'z'));
        }
    };

    check(F);
    check(H);

    Eof();
}

