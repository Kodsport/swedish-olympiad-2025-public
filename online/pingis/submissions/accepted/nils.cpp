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

int n, m;
const ll MAXN = 300001;
const int MAXL = 21;
const ll nils = 1000000007;

vector<set<int>> inds(MAXL, set<int>());
int nlog = 0;

vi solve(int h, int top){
    if(h == 0)return {top};
    if(sz(inds[h-1]) == 0)return {};
    int smallest = *(inds[h-1].begin());
    inds[h-1].erase(smallest);
    
    vi a1 = solve(h-1, min(top, smallest));
    vi a2 = solve(h-1, max(top, smallest));
    vi res = a1;
    trav(y, a2){
        res.push_back(y);
    }
    return res;

}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    cin >> n;

    int t = 1;
    while(t != n){
        t *= 2;
        nlog++;
    }

    rep(c1,0,n){
        int a;
        cin >> a;
        if(a > nlog){
            cout << "-1\n";
            return 0;
        }
        inds[a].insert(c1+1);
    }

    if(sz(inds[nlog]) != 1){
        cout << "-1\n";
        return 0;
    }

    int top = *(inds[nlog].begin());
    vi res = solve(nlog, top);

    if(sz(res) != n){
        cout << "-1\n";
        return 0;
    }

    rep(c1,0,n){
        cout << res[c1] << " ";
    }
    cout << "\n";

    return 0;
}
