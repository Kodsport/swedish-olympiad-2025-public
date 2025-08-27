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

vvl adj(6e5);
vl p;

ll dfs(int u, int last = -1){
    ll res = 0;
    ll am = 0;
    for(auto &v : adj[u]){
        if(v == last) continue;
        ll temp = dfs(v, u);
        res+=temp;
        if(temp > 0) am++;
    }
    res = max(res, p[u]);
    if(am == 1 && last == -1) res++;
    return res;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    ll from, to;
    p.resize(n);
    fo(i, n) cin >> p[i];
    fo(i, n-1){
        cin >> from >> to;
        adj[--from].pb(--to);
        adj[to].pb(from);
    }

    fo(i, n){
        if(p[i] == 1){
            ll res = dfs(i);
            cout << res/2ll+res%2ll << "\n";
            exit(0);
        }
    }
    cout << 0 << "\n";

    return 0;
}