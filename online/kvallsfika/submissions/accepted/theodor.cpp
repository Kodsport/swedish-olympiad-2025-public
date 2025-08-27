#include <bits/stdc++.h>
using namespace std;


#define ll long long
#define INF ((ll)(1e9+7))
#define fo(i, n) for(ll i=0;i<((ll)n);i++)
#define deb(x) cout << #x << " = " << (x) << endl;
#define deb2(x, y) cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl
#define pb push_back
#define F first
#define S second
#define LSOne(S) ((S) & (-S))
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
typedef vector<ll> vl;
typedef pair<ll, ll> pl;
typedef vector<pl> vpl;



int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, p, k;
    cin >> n >> p >> k;
    vl c(n), t(n);
    fo(i, n) cin >> c[i];
    fo(i, n) cin >> t[i];

    vpl v;
    fo(i, n){
        v.pb({c[i], t[i]});
    }
    sort(all(v));

    ll ans = 0;
    vl used(1e5+1, 0);

    fo(i, n){
        if(used[v[i].S]++>=k || p<v[i].F) continue;
        p-=v[i].F;
        ans++;
    }
    cout << ans;

    return 0;
}