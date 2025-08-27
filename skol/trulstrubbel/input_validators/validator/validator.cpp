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
    string s = Line();

    bool win_instant = Arg("win_instant", false);
    int a=0, b=0;
    rep(i,0,sz(s)){
        assert(s[i] == 'T' || s[i] == 'H');

        if (s[i] == 'H') a++;
        else b++;

        if (win_instant)
        {
            if (a>=11)
            {
                assert(a>=b+2);
                a = b = 0;
            }

            if (b>=11)
            {
                assert(b>=a+2);
                a = b = 0;
            }
        }
    }

    Eof();
}

