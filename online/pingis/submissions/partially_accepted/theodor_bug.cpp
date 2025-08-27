// Should only get 60p.

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

vl ans, v;
bool fail = 0;
ll d = -1;

void solve(vl &pos, vl &left){
    d++;
    ll n = pos.size();
    if(n == 1){
        if(d!=v[pos[0]]) fail = 1;
        ans[left[0]] = pos[0];
        return;
    }

    vl prev;
    vl next;
    fo(i, n){
        if(v[pos[i]]>d) next.pb(pos[i]);
        else prev.pb(pos[i]);
    }
    if(prev.size()!=next.size()){
        fail = 1;
        return;
    }
    vl nextLeft;
    fo(i, n/2){
        nextLeft.pb(left[i*2+((ll)next[i]>prev[i])]);
        ans[left[i*2+((ll)next[i]<prev[i])]] = prev[i];
    }
    solve(next, nextLeft);
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n;
    cin >> n;
    vl a(n), b(n);
    v.resize(n);
    fo(i, n){
        cin >> v[i];
        a[i] = b[i] = i;
    }
    ans.assign(n, -1);
    solve(a, b);
    if(fail) cout << -1;
    else{
        fo(i, n) cout << ans[i]+1 << " ";
    }


    return 0;
}