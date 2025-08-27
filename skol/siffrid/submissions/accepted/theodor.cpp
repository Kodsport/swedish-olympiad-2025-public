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
    
    ll x;
    cin >> x;
    ll sum = 0;
    string current = to_string(x);
    ll n = current.size();
    fo(i, n){
        sum += current[i]-'0';
    }
    string res(n, '0');
    ll left = sum-1;
    for(int i = n-1; i>=0&&left>0; i--){
        res[i]+=min(9ll, left);
        left-=9;
    }
    res[0]++;
    cout << res << " ";
    res = string(n, '0');
    left = sum;
    for(int i = 0; i<n&&left>0; i++){
        res[i]+=min(9ll, left);
        left-=9;
    }
    cout << res << "\n";



    return 0;
}