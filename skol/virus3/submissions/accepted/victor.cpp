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

string a,b;
ll n,m;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    cin>>b>>a;
    n=sz(a);
    m=sz(b);

    ll i=0;
    rep(j,0,m) {
        while(i<n&&a[i]!=b[j]) i++;
        if(i==n) {
            cout<<"Nej"<<endl;
            return 0;
        }
        i++;
    }
    cout<<"Ja"<<endl;
    return 0;
}