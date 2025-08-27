#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;

int n, m;
const ll MAXN = 151;
const ll nils = 1000000007;

vector<string> words;

bool substring(string w1, string w2){
    if(sz(w1) > sz(w2))return 0;
    rep(c1,0,sz(w2)-sz(w1)+1){
        rep(c2,0,sz(w1)){
            if(w1[c2] != w2[c1+c2])break;
            if(c2 == sz(w1)-1)return 1;
        }
    }
    return 0;
}

bool SEEN[MAXN][MAXN][MAXN] = {0};
bool MATCH[MAXN][MAXN][MAXN] = {0};

bool match(int i, int j, int start){
    // last letters of words[i] match with words[j]?
    if(SEEN[i][j][start])return MATCH[i][j][start];
    bool res = 1;
    rep(c1,0,sz(words[j])){
        if(c1+start >= sz(words[i]))break;
        if(words[j][c1] != words[i][c1+start])res = 0;
    }

    SEEN[i][j][start] = 1;
    MATCH[i][j][start] = res;
    return res;
}

ll POW[MAXN] = {0};

ll DP[MAXN][MAXN] = {0};
bool DPC[MAXN][MAXN] = {0};

ll dp(ll i, ll j){
    if(j < 0)return 0;
    if(j == 0)return 1;
    if(DPC[i][j])return DP[i][j];
    ll sum = 0;

    rep(start,1,sz(words[i])){
        rep(i2,0,m){
            if(match(i, i2, start)){
                ll d = sz(words[i2]) - sz(words[i]) + start;
                sum += dp(i2, j-d);
            }
        }
    }
    sum %= nils;

    rep(start,0,j){
        rep(i2,0,m){
            sum += POW[start] * dp(i2, j-start-sz(words[i2]));
            sum %= nils;
        }
    }

    ll ans = POW[j] + nils - sum;
    ans %= nils;
    DP[i][j] = ans;
    DPC[i][j] = 1;
    return ans;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    ll t = 1;
    rep(c1,0,MAXN){
        POW[c1] = t;
        t *= 26;
        t %= nils;
    }

    cin >> n >> m;
    vector<string> words2;
    rep(c1,0,m){
        string s;
        cin >> s;
        words2.push_back(s);
    }
    rep(c1,0,m){
        bool good = 1;
        rep(c2,0,m){
            if(c1 != c2 && substring(words2[c2], words2[c1])){
                good = 0;
                break;
            }
        }
        if(good){
            words.push_back(words2[c1]);
        }
    }
    m = sz(words);

    ll ans = 0;
    rep(start,0,n){
        rep(c1,0,m){
            ans += POW[start] * dp(c1, n-start-sz(words[c1]));
            ans %= nils;
        }
    }

    cout << (POW[n]-ans+nils)%nils << "\n";

    return 0;
}
