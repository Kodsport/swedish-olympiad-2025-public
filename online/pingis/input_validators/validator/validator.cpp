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

    int maxK = Arg("maxK", 19);
    int sorted = Arg("sorted", 0);

    int N = Int(1, 1<<maxK);
    Endl();

    vi a = SpacedInts(N,0,(int)1e9);

    // Check if all integers are sorted
    if (sorted == 1){
        rep(i,0,N-1) assert(a[i] <= a[i+1]);
    }

    // Check that N is a power of 2.
    assert (N ^ (LSOne(N)) == 0);

    Eof();
}

