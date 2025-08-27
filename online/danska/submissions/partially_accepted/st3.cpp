// m = 1, O(n*m*26)

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


vl b;
string subStr;
int n, m;
vvl memo;

void preProcess(string in){
    int i = 0, j = -1; b[0] = -1;
    while(i<in.length()){
        while(j>=0&&in[i]!=in[j]) j = b[j];
        i++; j++;
        b[i] = j;
    }
}

vl lengths;

ll dp(int pos, int l){
    if(pos == n) return 1;
    ll &ans = memo[pos][l];
    if(ans != -1) return ans;
    ans = 0;
    fo(i, 26){
        int j = lengths[pos];
        while(j>=0&& i+'a' != subStr[j]) j = b[j];
        j++;
        if(j==subStr.length()){
            continue;
        }
        lengths[pos+1] = j;
        ans = (ans+dp(pos+1, j))%INF;
    }
    return ans;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    subStr.resize(m+2);
    b.assign(n+2, 0);
    cin >> subStr;
    preProcess(subStr);

    memo.assign(n+2, vl(n+2, -1));
    lengths.assign(n+2, 0);

    cout << dp(0, 0) << "\n";

    return 0;
}