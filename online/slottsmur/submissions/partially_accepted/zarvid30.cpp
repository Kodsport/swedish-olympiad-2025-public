#include <bits/stdc++.h>

#define all(x)  (x).begin(), (x).end()
#define rall(x)  (x).rbegin(), (x).rend()

using namespace std;

typedef long long ll;

ll linf = 1e15+1;

inline void scoobydoobydoo(){
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}

const int MAXN = 2e5+3;

pair<ll, ll> ST[4*MAXN];
ll leftOf[4*MAXN], rightOf[4*MAXN];
ll vals[MAXN];
ll indexToNode[MAXN];

void init_ST(ll l, ll r, ll node=1){
    leftOf[node] = l; rightOf[node] = r;
    if (l == r){
        ST[node] = {vals[l], vals[l]};
        indexToNode[l] = node;
        return;
    }  
    ll mid = (l+r)>>1;
    init_ST(l, mid, 2*node);
    init_ST(mid+1, r, 2*node+1);
    ST[node].first = max(ST[2*node].first, ST[2*node+1].first);
    ST[node].second = ST[2*node].second + ST[2*node+1].second;
    return;
}

vector<ll> find_mothers(ll l, ll r, ll node=1){
    if (leftOf[node] == l && rightOf[node] == r){
        return {node};
    }
    ll a = 2*node, b = 2*node+1;
    if (l >= leftOf[b])return find_mothers(l, r, b);
    if (r <= rightOf[a])return find_mothers(l, r, a);
    vector<ll> v1 = find_mothers(l, rightOf[a], a);
    vector<ll> v2 = find_mothers(leftOf[b], r, b);
    for (ll x : v2)v1.push_back(x);
    return v1;
}

ll leftest(ll node, ll w){
    if (leftOf[node] == rightOf[node])return leftOf[node];
    ll a = 2*node, b = 2*node+1;
    if (ST[a].first > w)return leftest(a, w);
    return leftest(b, w);
}

ll left_query(ll l, ll r, ll v){ //first stricly bigger than v in range l -> r
    if (l > r)return -1;
    vector<ll> mothers = find_mothers(l, r);
    for (ll x : mothers){
        if (ST[x].first > v)return leftest(x, v);
    }
    return -1;
}

ll rightest(ll node, ll w){
    if (leftOf[node] == rightOf[node])return leftOf[node];
    ll a = 2*node, b = 2*node+1;
    if (ST[b].first > w)return rightest(b, w);
    return rightest(a, w);
}

ll right_query(ll l, ll r, ll v){ //last stricly bigger than v in range l -> r
    if (l > r)return -1;

    vector<ll> mothers = find_mothers(l, r);
    reverse(all(mothers));
    for (ll x : mothers){
        if (ST[x].first > v)return rightest(x, v);
    }
    return -1;
}

ll sum(ll l, ll r){
    vector<ll> mothers = find_mothers(l, r);
    ll suml = 0;
    for (ll x : mothers)suml += ST[x].second;
    return suml;
}

void update(ll index, ll increment){
    vals[index] += increment;
    ll node = indexToNode[index];
    ST[node] = {vals[index], vals[index]};
    for (ll curr = node/2; curr != 0; curr /= 2){
        ST[curr].first = max(ST[2*curr].first, ST[2*curr+1].first);
        ST[curr].second = ST[2*curr].second + ST[2*curr+1].second;
    }
}   

int main(){
    scoobydoobydoo();
    ll n, q; cin >> n >> q;
    for (int i = 0; i < n; i++)cin >> vals[i];
    init_ST(0, n-1);

    while (q--){
        ll k, l, r; cin >> k >> l >> r;
        if (k == 1){
            l--; r--;
            set<ll> s;
            ll fir = left_query(l, r, 0);
            while (fir != -1){
                s.insert(fir);
                fir = left_query(fir+1, r, vals[fir]);
            }

            ll last = right_query(l, r, 0);
            while (last != -1){
                s.insert(last);
                last = right_query(l, last-1, vals[last]);
            }

            ll sumi = 0;

            last = -1;
            ll maxi = -1;


            for (ll x : s){
                maxi = max(maxi, vals[x]);
                if (last != -1)sumi += abs(last-x)*min(vals[last], vals[x]);
                last = x;
            }
            cout << sumi + maxi - sum(l, r) << endl;
            
        } else {
            l--;
            update(l, r);
        }
    }

    return 0;
}