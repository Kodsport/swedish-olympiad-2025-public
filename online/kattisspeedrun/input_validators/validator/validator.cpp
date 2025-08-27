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
    int s = Int(0, int(1e5));
    Endl();
    int p = Int(1, Arg("maxp", int(1e5)));
    Endl();
    assert(s*2<p);
    int a = Int(1, int(1e5));
    Endl();
    int b = Int(1, int(1e5));
    Endl();

    if (Arg("b_large", 0)) assert(a==1 && b==int(1e5));
    if (Arg("a_large", 0)) assert(b==1 && a==int(1e5));


    Eof();
}

