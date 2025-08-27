#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define ar array
#define vo vector
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

#define rep(i, a, b) for(ll i=(a); i<(b); i++) 
#define repd(i, a, b) for(ll i=(a); i>=(b); i--) 

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, m;
    cin >> n >> m;

    const ll mxn=1e6;
    ll memo[mxn];
    memset(memo, 0x3f, sizeof memo);

    ll ans = 0;
    while(n>=mxn) {
        n-=(n%m);
        n/=m;
        ans+=2;
    }

    memo[n]=0;
    repd(i, n, 0) {
        if(memo[i]>=ll(1e12)) 
            continue;

        rep(j, 1, min(i+1, m)) 
            memo[i-j]=min(memo[i-j], memo[i]+1);

        if(!(i%m)) 
            memo[i/m]=min(memo[i/m], memo[i]+1);
    }

    cout << ans+memo[0];
}
