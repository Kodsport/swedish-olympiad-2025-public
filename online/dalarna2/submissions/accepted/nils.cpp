#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;

int n;
const ll MAXN = 500001;
const ll nils = 1000000007;
vector<vi> C(MAXN, vi());

vector<set<int>> not_computed(MAXN, set<int>());
map<ll,ll> M;
ll SUM[MAXN] = {0};

ll P[MAXN] = {0};


ll dp(ll i, ll to){
    vi upd;
    ll h = i*MAXN+to;
    if(M.find(h) != M.end())return M[h];
    trav(y, not_computed[i]){
        if(y != to){
            SUM[i] += dp(y, i);
            upd.push_back(y);
        }
    }
    trav(y, upd){
        not_computed[i].erase(y);
    }
    ll sum = SUM[i];
    if(to != -1 && not_computed[i].find(to) == not_computed[i].end()){
        sum -= dp(to, i);
    }

    ll ans = max(sum, P[i]);
    M[h] = ans;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;
    rep(c1,0,n){
        cin >> P[c1];
    }
    rep(c1,0,n-1){
        int a,b;
        cin >> a;
        cin >> b;
        a--;
        b--;
        C[a].push_back(b);
        C[b].push_back(a);
        not_computed[a].insert(b);
        not_computed[b].insert(a);
    }

    ll ans = nils*nils;
    rep(c1,0,n){
        vl W;
        ll tot = 0;
        trav(y, C[c1]){
            ll x = dp(y, c1);
            tot += x;
            W.push_back(x);
        }
        sort(all(W));
        ll last = W.back();
        ll rest = tot-last;
        if(last <= rest){
            tot -= tot/2;
        }
        else{
            tot -= rest;
        }

        ans = min(ans, max(tot, P[c1]));
    }
    cout << ans << "\n";

    return 0;
}
