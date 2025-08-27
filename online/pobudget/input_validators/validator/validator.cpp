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
    int n = Int(1, 30);
    Endl();
    int lb = Arg("lb");
    int ub = Arg("ub");

    for (int i = 0; i < n; i++)
    {
        string s = Line();
        assert(s.size() > 0 && s.size() <= 30);
        Int(lb, ub);
        Endl();
    }
    
    
    Eof();
}

