using namespace std;
#include <bits/stdc++.h>

typedef long long ll;
#define rep(i,a,b) for(int i = a; i < b; i++)

int main() {
    ll n, p, k;
    cin >> n >> p >> k;

    vector<pair<ll,ll>> arr(n);
    rep(i,0,n) cin >> arr[i].first;
    rep(i,0,n) cin >> arr[i].second;
    vector<ll> used(100100, 0);

    sort(arr.begin(), arr.end());

    ll ans = 0;
    for (auto [c, t] : arr) {
        if (used[t] == k || p - c < 0) continue;
        used[t]++;
        ans++;
        p -= c;
    }
    cout << ans << endl;
}