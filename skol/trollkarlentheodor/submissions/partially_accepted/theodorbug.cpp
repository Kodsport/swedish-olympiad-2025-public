#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define INF ((ll)(1e9+7))
#define fo(i, n) for(ll i=0;i<((ll)n);i++)
#define deb(x) cout << #x << " = " << (x) << endl;
#define deb2(x, y) cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define LSOne(S) ((S) & (-S))
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
typedef pair<int, int> pii;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pii> vpii;
typedef vector<pl> vpl;
typedef vector<vi> vvi;
typedef vector<vl> vvl;
typedef vector<vpii> vvpii;
typedef vector<vpl> vvpl;



int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, a, s;
    cin >> n >> s >> a;
    vl h(n);
    fo(i, n) cin >> h[i];

    ll lo = -1;
    ll hi = 2e10; // mid * a can now overflow ll (cannot lower hi much)
    while(hi-lo>1){
        ll mid = (hi+lo) / 2;
        ll ans = 0;
        fo(i, n){
            ans+=max(0ll, h[i]-a*mid+s-1ll)/s;
        }
        if(ans<=mid) hi = mid;
        else lo = mid;
    }
    cout << hi << "\n";


    return 0;
}