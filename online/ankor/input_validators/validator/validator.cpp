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

#define LSOne(S) ((S) & (-S))


void run() {
    int setN = Arg("n", -1);
    int maxN = Arg("nmax", 100000);
    int maxX = Arg("xmax", 1000000000);
    int forceX = Arg("x", -1);

    int N = Int(1, maxN);
    if(setN != -1) assert(N == setN);
    Endl();

    set<pair<int,int>> points;
    for(int i = 0; i < 2*N; i++){
        int x = Int(0, maxX);
        Space();
        int y = Int(0, 1000000000);
        Endl();

        if(forceX != -1) {
            assert(x == forceX);
        }
        assert(points.count({x, y}) == 0);
        points.insert({x, y});
    }

    Eof();
}

