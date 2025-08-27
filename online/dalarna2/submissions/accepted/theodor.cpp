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
vl p, needed;

ll dfs(int u, int last = -1){
    ll &res = needed[u];
    for(auto &v : adj[u]){
        if(v == last) continue;
        res+=dfs(v, u);
    }
    res = max(res, p[u]);
    return res;
}

ll dfs2(int u, ll passing = 0, int last = -1){
    ll ans = 0, sum = 0;
    pl heavyEdge = {0, -1};
    for(auto &v : adj[u]){
        if(v == last) continue;
        sum+=needed[v];
        heavyEdge = max(heavyEdge, {needed[v], v});
    }
    sum-=heavyEdge.F;
    if(sum+passing>=heavyEdge.F){
        ans=abs(passing-heavyEdge.F);
        sum-=ans;
        ans+=min(heavyEdge.F, passing);
        if(sum>0) ans+=sum/2ll+sum%2ll;
        return max(ans, p[u]);
    }
    return dfs2(heavyEdge.S, max(passing+sum, p[u]), u);
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

    needed.assign(n, 0);
    dfs(0);
    cout << dfs2(0) << "\n";

    return 0;
}