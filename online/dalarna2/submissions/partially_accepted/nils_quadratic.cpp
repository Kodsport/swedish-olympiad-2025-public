#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;

int n;
const int MAXN = 500001;
const ll nils = 1000000007;
vector<vi> C(MAXN, vi());

ll P[MAXN] = {0};

ll dfs(int i, int par){
    if(par != -1){
        ll tot = 0;
        trav(y, C[i]){
            if(y != par){
                tot += dfs(y, i);
            }
        }
        return max(tot, P[i]);
    }

    vl X;
    ll tot = 0;
    trav(y, C[i]){
        ll x = dfs(y, i);
        tot += x;
        X.push_back(x);
    }
    sort(all(X));
    ll last = X.back();
    ll rest = tot-last;

    if(last <= rest){
        tot -= tot/2;
    }
    else{
        tot -= rest;
    }
    return max(tot, P[i]);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;
    rep(c1,0,n){
        cin >> P[c1];
    }
    rep(c1,0,n-1){
        int a,b;
        cin >> a;
        cin >> b;
        a--;
        b--;
        C[a].push_back(b);
        C[b].push_back(a);
    }

    ll ans = nils*nils;
    rep(c1,0,n){
        ans = min(ans, dfs(c1,-1));
    }
    cout << ans << "\n";

    return 0;
}
