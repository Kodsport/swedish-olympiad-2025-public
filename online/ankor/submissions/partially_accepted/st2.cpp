#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<long long> ys;
    for(int i = 0; i < 2*n; i++) {
        int x, y; cin >> x >> y;
        ys.push_back(y);
    }
    sort(ys.begin(), ys.end());
    double b = (ys[n-1] + ys[n]) / 2.0 + 0.1;
    cout << "0 " << b << endl;
    return 0;
}