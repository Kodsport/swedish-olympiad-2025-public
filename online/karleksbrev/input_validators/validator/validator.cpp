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
    int k_is = (int)Arg("k");
    int n = Int(100, 100); Space();
    int k = Int(k_is, k_is); Endl();

    int test_type = Int(0, 5); Space();
    Int(0, int(1e9)); Endl();

    bool size1 = (bool)Arg("size1", 0);
    if (size1) assert(test_type==1);

    bool evenends = (bool)Arg("evenends", 0);
    if (evenends) assert(test_type==2);

    bool lefteven = (bool)Arg("lefteven", 0);
    if (lefteven) assert(test_type==3);


    Eof();
}

