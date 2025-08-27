using namespace std;
#include <bits/stdc++.h>

#define rep(i,a,b) for (int i = a; i < b; i++)
#define pb push_back

typedef long long ll;
typedef vector<ll> vi;

int n;
vector<pair<int,int>> arr;
vector<int> ans;

void solve(int offset, vector<int> & arr) {
    if (arr.size() == 1) {
        ans[offset] = arr[0];
        return;
    }

    if (arr[0] > arr[1]) swap(arr[0], arr[1]);

    vector<int> a, b;
    int i = 1;
    int j = 2;
    a.push_back(arr[0]);
    b.push_back(arr[1]);

    while (j < arr.size()) {
        rep(k,0,i) {
            a.push_back(arr[j]);
            j++;
        }
        rep(k,0,max(i,1)) {
            b.push_back(arr[j]);
            j++;
        }
        i *= 2;
    }

    solve(offset, a);
    solve(offset + a.size(), b);
}

int main() {
    cin >> n;
    arr.resize(n);
    ans.resize(n);
    rep(i,0,n) arr[i].second = -i;
    rep(i,0,n) cin >> arr[i].first;

    sort(arr.rbegin(), arr.rend());
    bool yes = true;
    if (n == 1 && arr[0].first != 0) yes = false;
    int N = n, w = 0;
    for (int i = n-1; i >= 0; i--) {
        if (arr[i].first != w) yes = false;
        if (i == N / 2) {
            w++;
            N /= 2;
        }
    }
    if (!yes) {
        cout << -1 << endl;
        return 0;
    }

    vector<int> a(n);
    rep(i,0,n) a[i] = 1-arr[i].second;

    solve(0, a);

    rep(i,0,n) cout << ans[i] << " "; cout << endl;
}