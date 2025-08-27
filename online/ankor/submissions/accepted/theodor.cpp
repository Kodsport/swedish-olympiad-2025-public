// O(n log(n))

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
    cout << fixed << setprecision(10);
    cin.tie(0)->sync_with_stdio(0);


    double lutning = 0.123954323562;
    ll n, x, y;
    cin >> n;
    vector<long double> dis;
    fo(i, n*2){
        cin >> x >> y;
        dis.pb(-lutning*x+y);
    }
    sort(all(dis));
    cout << lutning << " " << (dis[n]+dis[n-1])/2 << "\n";
    
    return 0;
}