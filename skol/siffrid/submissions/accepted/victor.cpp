// #pragma GCC target ("avx,avx2,fma")
// #pragma GCC optimize ("Ofast,inline") // O1 - O2 - O3 - Os - Ofast
// #pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (ll i = (a); i < (b); ++i)
#define per(i, a, b) for (ll i = (b) - 1; i >= (a); --i)
#define trav(a, x) for (auto &a : x)

#define all(x) x.begin(), x.end()
#define sz(x) (ll)x.size()
#define pb push_back
#define debug(x) cout<<#x<<" = "<<x<<endl

#define umap unordered_map
#define uset unordered_set

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;

typedef long long ll;
typedef pair<ll,ll> pll;
typedef pair<ll,pll> ppll;
typedef vector<ll> vll;
typedef vector<pll> vpll;
typedef vector<vll> vvll;

const ll INF = 1'000'000'007;

ll x,n;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    ll numsum=0;
    cin>>x;
    n=sz(to_string(x));
    trav(digit,to_string(x)) numsum+=digit-'0';

    {
        string mn="";
        ll target=numsum;
        rep(i,0,n) {
            rep(j,i==0,10) {
                if(target-j<=(n-i-1)*9) {
                    target-=j;
                    mn+=to_string(j);
                    break;
                }
            }
        }
        cout<<mn<<' ';
    }

    {
        string mx="";
        ll target=numsum;
        rep(i,0,n) {
            ll val=min(target,9LL);
            target-=val;
            mx+=to_string(val);
        }
        cout<<mx<<endl;
    }

    return 0;
}