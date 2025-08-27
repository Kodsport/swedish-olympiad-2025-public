// print all solutions, not just count
using namespace std;
#include <bits/stdc++.h>

#define rep(i,a,b) for (int i = a; i < b; i++)
#define pb push_back

typedef long long ll;
typedef vector<ll> vi;

ll n, k, s, a;

set<vector<ll>> allans;
ll answer(vector<ll> & arr) {
    ll low = -1, high = 1e9, mid;
    while (high - low > 1) {
        mid = (low + high) / 2;
        ll ans = 0;
        rep(i,0,n) ans += max(0ll, (arr[i] - mid * a + s - 1) / s);
        if (ans <= mid) high = mid;
        else low = mid;
    }
    if (high==k)
    {
        allans.insert(arr);
    }
    return high;
}

void recur(vector<ll> & count, vector<ll> & arr, int i, bool changed) {
    ll ans = answer(arr);
    if (changed) count[ans]++;
    if (ans <= k) {
        arr[i]++;
        recur(count, arr, i, true);
        arr[i]--;
    }
    i++;
    if (i < n) recur(count, arr, i, false);
}

int main() {
    cin >> n >> k >> s >> a;
    vector<ll> arr(n, 1);
    vector<ll> count(k+2, 0);
    recur(count, arr, 0, true);
    for (auto sol : allans)
    {
        for (auto e : sol) cout << e << " ";
        cout << "\n";
    }
}