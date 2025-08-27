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

double lutning = 0.123954323562;
vpl points;

ll splitAmount(double b){
    int am = 0;
    for(auto &[x, y] : points) {
        if(y > lutning * (x+1ll) + b) am++;
    }
    return am;
}


int main() {
    cout << fixed << setprecision(10);
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    points.resize(2*n);
    for(auto &[x, y] : points) cin >> x >> y;

    long double lo = -1e10, hi = 1e10;
    while(true){
        long double mid = (lo + hi) / 2;
        ll res = splitAmount(mid);
        if(res == n) {
            cout << mid-lutning << " " << res << "\n";
            exit(0);
        }
        if(res > n) hi = mid;
        else lo = mid;
    }

    return 0;
}