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

    ll s, p, a, b;
    cin >> s >> p >> a >> b;
    if(s>p/2){
        cout << 0;
        exit(0);
    }
    ll am = p+1;
    am -= am/2+s;
    ll am2 = p-2ll*s;
    if(s+am2==(p+am2)/2) am2++;
    ll am3 = p+2;
    am3 -= am3/2+s+1;
    ll am4 = p-2ll*(s+1ll);
    if(s+1+am4==(p+am4)/2) am4++;

    cout << min(min(am*a, am2*b), min(am3*a+b, am4*b+a));

    return 0;
}