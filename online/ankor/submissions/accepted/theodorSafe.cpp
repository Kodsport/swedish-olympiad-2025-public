// O(n log(n))

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
template <class result_t=std::chrono::milliseconds,class clock_t=std::chrono::steady_clock,class duration_t = std::chrono::milliseconds>
auto since(std::chrono::time_point<clock_t, duration_t> const& start){return std::chrono::duration_cast<result_t>(clock_t::now() - start);}
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<pl> vpl;
typedef vector<vl> vvl;
typedef vector<vpl> vvpl;


int main() {
    cout << fixed << setprecision(10);
    cin.tie(0)->sync_with_stdio(0);
    auto start = std::chrono::steady_clock::now();

    ll n, x, y;
    cin >> n;
    vpl points;
    fo(i, n*2){
        cin >> x >> y;
        points.pb({x, y});
    }

    mt19937_64 rng(1337);
    uniform_real_distribution<long double> randomLutning(-1.0, 1.0);
    vector<long double> res = {-1, -1, -1};
    while(since(start).count()<500){
        long double lutning = randomLutning(rng);
        vector<long double> dis;
        fo(i, n*2){
            tie(x, y) = points[i];
            dis.pb(-lutning*x+y);  
        }
        sort(all(dis));
        res = max(res, vector<long double>{dis[n]-dis[n-1], lutning, (dis[n]+dis[n-1])/2ll});
    }
    cout << res[1] << " " << res[2] << "\n";
    
    return 0;
}