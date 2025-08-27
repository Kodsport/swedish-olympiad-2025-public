#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=(a); i < (b); i++)
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()
typedef vector<int> vi;
typedef long long ll;
typedef pair<int,int> pii;

vi curr(11,0);
ll a,s;

ll solve(ll m){
    ll temp = 0;
    rep(i,0,sz(curr)){
        if (curr[i] >= m || a == 0) // blir m*a overflow??
            temp += (curr[i]-m*a + s-1)/s;
    }

    return temp;
}

int main(){

    int n;

    cin >> n >> s >> a;

    rep(i,0,n) cin >> curr[i];

    ll l = 0;
    ll r = 1e18;    
    while (l<r){
        ll m = (l+r)/2;

        ll res = solve(m);
        if (res > m)
            l = m+1;
        else{
            r = m;
        }
    }

    cout << l << "\n";

}