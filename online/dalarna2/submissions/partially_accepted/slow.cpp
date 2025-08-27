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

vvl adj(2e5);
int n;

vl dfs(int u, int goal, int last){
    if(u == goal) return {goal};
    for(auto &v : adj[u]){
        if(v == last) continue;
        vl temp = dfs(v, goal, u);
        if(temp[0] != -1){
            temp.pb(u);
            return temp;
        }
    }
    return {-1};
}

map<vl, ll> memo;

ll solve(vl current){
    if(memo[current]) return memo[current];
    ll sum = 0;
    fo(i, current.size()) sum+=current[i];
    if(sum == 0) return 0;
    ll ans = 1e18;
    fo(i, n){
        if(adj[i].size()>1) continue;
        for(ll j = i; j<n; j++){
            if(adj[j].size()>1) continue;
            vl path = dfs(i, j, -1);
            bool possible = 0;
            vl next = current;
            for(auto &v : path){
                if(current[v]) possible = 1;
                next[v]=max(0ll, next[v]-1);
            }
            if(possible)ans = min(ans, solve(next)+1);
        }
    }
    return memo[current] = ans; 
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    ll from, to;
    vl p(n);
    fo(i, n) cin >> p[i];
    fo(i, n-1){
        cin >> from >> to;
        adj[--from].pb(--to);
        adj[to].pb(from);
    }
    
    cout << solve(p);

    return 0;
}