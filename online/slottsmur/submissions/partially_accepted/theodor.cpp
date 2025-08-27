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

vl stV, stSum;
vl h;

void construct(ll l, ll r, ll pos = 1){
    if(r-l == 1){
        while(stV.size()<=pos) stV.pb(0);
        while(stSum.size()<=pos) stSum.pb(0);
        stSum[pos] = stV[pos] = h[l];
    }else{
        ll mid = (r+l) / 2ll;
        construct(l, mid, pos*2);
        construct(mid, r, pos*2+1);
        stV[pos] = max(stV[pos*2], stV[pos*2+1]);
        stSum[pos] = stSum[pos*2] + stSum[pos*2+1];
    }
}

void update(ll updatePos, ll val, ll l, ll r, ll pos = 1){
    if(r-l == 1){
        stSum[pos] = stV[pos] = val;
        return;
    }
    ll mid = (r+l) / 2ll;
    if(updatePos < mid) update(updatePos, val, l, mid, pos*2);
    else update(updatePos, val, mid, r, pos*2+1);
    stV[pos] = max(stV[pos*2], stV[pos*2+1]);
    stSum[pos] = stSum[pos*2] + stSum[pos*2+1];
}

ll queryl(ll lo, ll hi, ll val, ll l, ll r, ll pos = 1){
    if(r <= lo || hi <= l) return -1;
    ll mid = (r+l) / 2ll;
    if(lo <= l && r <= hi){
        if(stV[pos] <= val) return -1;
        if(r-l == 1) return l;
        if(stV[pos*2] > val) return queryl(lo, hi, val, l, mid, pos*2);
        return queryl(lo, hi, val, mid, r, pos*2+1);
    }
    ll res = queryl(lo, hi, val, l, mid, pos*2);
    if(res == -1) res = queryl(lo, hi, val, mid, r, pos*2+1);
    return res;
}

ll queryr(ll lo, ll hi, ll val, ll l, ll r, ll pos = 1){
    if(r <= lo || hi <= l) return -1;
    ll mid = (r+l) / 2ll;
    if(lo <= l && r <= hi){
        if(stV[pos] <= val) return -1;
        if(r-l == 1) return l;
        if(stV[pos*2+1] > val) return queryr(lo, hi, val, mid, r, pos*2+1);
        return queryr(lo, hi, val, l, mid, pos*2);
    }
    ll res = queryr(lo, hi, val, mid, r, pos*2+1);
    if(res == -1) res = queryr(lo, hi, val, l, mid, pos*2);
    return res;
}

ll querySum(ll lo, ll hi, ll l, ll r, ll pos = 1){
    if(r <= lo || hi <= l) return 0;
    if(lo <= l && r <= hi) return stSum[pos];
    ll mid = (r+l) / 2ll;
    return querySum(lo, hi, l, mid, pos*2) + querySum(lo, hi, mid, r, pos*2+1);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, q;
    cin >> n >> q;
    h.resize(n);
    fo(i, n) cin >> h[i];

    ll t, pos;
    construct(0, n);
    while(q--){
        cin >> t >> pos;
        pos--;
        if(t == 1){
            ll l = pos, r;
            cin >> r;
            r--;
            ll ans = -querySum(l, r+1, 0, n);
            ll lval = h[l], rval = h[r];
            while(l<r){
                if(lval<rval){
                    ll next = queryl(l, r+1, lval, 0, n);
                    if(next == -1) break;
                    ans+=lval*(next-l);
                    l = next;
                    lval = max(h[l], lval);
                }else{
                    ll next = queryr(l, r+1, rval, 0, n);
                    if(next == -1) break;
                    ans+=rval*(r-next);
                    r = next;
                    rval = max(h[r], rval);
                }
            }
            cout << ans+(r-l+1)*lval << "\n";
        }else{
            ll val;
            cin >> val;
            h[pos]+=val;
            update(pos, h[pos], 0, n);
        }
    }
   
    exit(0);
}
