// O((n^2*m+n*m^2)*26)

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


vvl b;
vector<string> subStr;
int co = 0;
int n, m;
vector<vvl> memo;

void preProcess(string in){
    int i = 0, j = -1; b[co][0] = -1;
    while(i<((ll)in.length())){
        while(j>=0&&in[i]!=in[j]) j = b[co][j];
        i++; j++;
        b[co][i] = j;
    }
}

vector<vvl> lengths;
vector<vvpl> nextRem;
vvl seen;

ll dp(int pos, int l, int ind){
    if(pos == n) return 1;
    ll &ans = memo[pos][l][ind];
    if(ans != -1) return ans;
    ans = 0;

    if(!seen[l][ind]){
        seen[l][ind] = 1;
        fo(i, 26){
            bool fail = 0;
            pl next = {0, 0};
            vl temp(m);
            fo(k, m){
                int j = lengths[l][ind][k];
                while(j>=0&& i+'a' != subStr[k][j]) j = b[k][j];
                j++;
                if(j==((ll)subStr[k].length())){
                    fail = 1;
                    break;
                }
                temp[k] = j;
                next = max(next, {j, k});
            }
            if(fail) continue;
            lengths[next.F][next.S] = temp;
            // ans = (ans+dp(pos+1, next.F, next.S))%INF;
            nextRem[l][ind].pb({next.F, next.S});
        }
    }

    ll a1, a2;
    fo(i, nextRem[l][ind].size()){
        tie(a1, a2) = nextRem[l][ind][i];
        ans = (ans+dp(pos+1, a1, a2))%INF;
    }
    return ans;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    subStr.resize(m+2);
    b.assign(m+2, vl(n+2, 0));
    fo(i, m){
        cin >> subStr[i];
        preProcess(subStr[i]);
        co++;
    }

    memo.assign(n+2, vvl(n+2, vl(m+2, -1)));
    lengths.assign(n+2, vvl(m+2, vl{}));
    lengths[0][0] = vl(m, 0);
    seen.assign(n+2, vl(m+2, 0));
    nextRem.assign(n+2, vvpl(m+2, vpl{}));

    cout << dp(0, 0, 0) << "\n";

    return 0;
}