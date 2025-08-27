#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<pair<int,int>> points(2*n);
    for(int i = 0; i < 2*n; i++) {
        cin >> points[i].first >> points[i].second;
    }
    sort(points.begin(), points.end());
    
    double m = 0.1;
    double b = (points[n-1].second + points[n].second) / 2.0;
    cout << m << " " << b << endl;
    return 0;
}