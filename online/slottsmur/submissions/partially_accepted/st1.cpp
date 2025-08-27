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
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pl> vpl;
typedef vector<vl> vvl;
typedef vector<vpl> vvpl;



int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, q;
    cin >> n >> q;
    vl h(n);
    fo(i, n) cin >> h[i];

    ll t, pos;
    while(q--){
        cin >> t >> pos;
        pos--;
        if(t == 1){
            ll l = pos, r;
            cin >> r;
            r--;
            ll ans = 0;
            ll lval = h[l], rval = h[r];
            while(l<r){
                if(lval<rval){
                    lval = max(h[++l], lval);
                    ans+=lval-h[l];
                }else{
                    rval = max(h[--r], rval);
                    ans+=rval-h[r];
                }
            }
            cout << ans << "\n";
        }else{
            ll val;
            cin >> val;
            h[pos]+=val;
        }
    }
   
    exit(0);
}