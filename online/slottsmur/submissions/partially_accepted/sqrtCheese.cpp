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

ll query(ll lo, ll hi, ll l, ll r, ll pos = 1){
    if(r <= lo || hi <= l) return -1;
    ll mid = (r+l) / 2ll;
    if(lo <= l && r <= hi){
        if(r-l == 1) return l;
        if(stV[pos*2] > stV[pos*2+1]) return query(lo, hi, l, mid, pos*2);
        return query(lo, hi, mid, r, pos*2+1);
    }
    ll res = query(lo, hi, l, mid, pos*2);
    ll res2 = query(lo, hi, mid, r, pos*2+1);
    if(res == -1) return res2;
    if(res2 == -1) return res;
    if(h[res] > h[res2]) return res;
    return res2;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    ll n, q, block_size = 500;
    cin >> n >> q;
    h.resize(n);
    fo(i, n) cin >> h[i];
    construct(0, n);

    vector<unordered_map<ll, pl>> blocksL(n/block_size+2); // height, (res, next_height)
    vector<unordered_map<ll, pl>> blocksR(n/block_size+2);
    ll t, pos;
    while(q--){
        cin >> t >> pos;
        pos--;
        if(t == 1){
            ll l = pos, r;
            cin >> r;
            r--;
            ll mid = query(l, r+1, 0, n);
            ll ans = 0;
            ll lval = h[l], rval = h[r];
            while(l<mid){
                if(l/block_size != mid/block_size && l%block_size == 0){
                    if(blocksL[l/block_size].count(lval)){
                        ans += blocksL[l/block_size][lval].F;
                        lval = blocksL[l/block_size][lval].S;
                        l+=block_size;
                        continue;
                    } 
                    ll next_height = lval;
                    ll rPos = l+block_size;
                    ll sum = -querySum(l, rPos, 0, n);
                    while(l < rPos){
                        ll res = queryl(l, rPos, next_height, 0, n);
                        if(res == -1){
                            sum += (rPos-l)*next_height;
                            l = rPos;
                            break;
                        }
                        sum += next_height*(res-l);
                        next_height = max(next_height, h[res]);
                        l = res;
                    }
                    next_height = max(next_height, h[l]);
                    blocksL[(l/block_size)-1][lval] = {sum, next_height};
                    ans += sum;
                    lval = next_height;
                    continue;
                }
                lval = max(h[l], lval);
                ans += lval - h[l++];
                lval = max(h[l], lval);
            }
            while(r>mid){
                if(r/block_size > mid/block_size && r%block_size == block_size-1){
                    if(blocksR[r/block_size].count(rval)){
                        ans += blocksR[r/block_size][rval].F;
                        rval = blocksR[r/block_size][rval].S;
                        r-=block_size;
                        continue;
                    }
                    ll next_height = rval;
                    ll lPos = r-block_size;
                    ll sum = -querySum(lPos+1, r+1, 0, n);
                    while(r >= lPos){
                        ll res = queryr(lPos+1, r+1, next_height, 0, n);
                        if(res == -1){
                            sum += (r-lPos)*next_height;
                            r = lPos;
                            break;
                        }
                        sum += next_height*(r-res);
                        next_height = max(next_height, h[res]);
                        r = res;
                    }
                    next_height = max(next_height, h[r]);
                    blocksR[(r/block_size)+1][rval] = {sum, next_height};
                    ans += sum;
                    rval = next_height;
                    continue;
                }
                rval = max(h[r], rval);
                ans += rval - h[r--];
                rval = max(h[r], rval);
            }
            cout << ans << "\n";
        }else{
            ll val;
            cin >> val;
            h[pos]+=val;
            update(pos, h[pos], 0, n);
            blocksL[pos/block_size].clear();
            blocksR[pos/block_size].clear();
        }
    }
   
    exit(0);
}