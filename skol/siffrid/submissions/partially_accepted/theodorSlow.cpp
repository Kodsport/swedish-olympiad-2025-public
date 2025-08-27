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

string current;
ll ma = -1;
ll mi = 1e18;
vvl memo;

void rec(int pos, int sum){
    if(pos == -1){
        if(sum != 0) return;
        ll val = stol(current);
        ma = max(ma, val);
        mi = min(mi, val);
        return;
    }
    fo(i, min(10, sum+1)){
        if(!pos&&!i) continue;
        current[pos]=i+'0';
        rec(pos-1, sum-i);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    
    ll x;
    cin >> x;
    string curr = to_string(x);
    ll sum = 0;
    ll n = curr.size();
    fo(i, n) sum+=curr[i]-'0';

    current = string(n, '0');
    rec(n-1, sum);
    cout << mi << " " << ma;


    return 0;
}