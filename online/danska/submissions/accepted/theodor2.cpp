// O(n^2*m*26)

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


int n, m;
vvl memo;

struct Node{
    vl next = vl(26, -1);
    int fail = -1;
    bool end = 0;
};

vector<Node> trie(1);

ll dp(int pos, int triePos){
    if(trie[triePos].end) return 0;
    if(pos == n) return 1;
    ll &ans = memo[pos][triePos];
    if(ans != -1) return ans;
    ans = 0;
    fo(i, 26){
        ans = (ans+dp(pos+1, trie[triePos].next[i]))%INF;
    }
    return ans;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> n >> m;

    string in;
    fo(i, m){
        cin >> in;
        int node = 0;
        for(char c : in){
            if(trie[node].next[c-'a'] == -1){
                trie[node].next[c-'a'] = trie.size();
                trie.pb(Node());
            }
            node = trie[node].next[c-'a'];
        }
        trie[node].end = 1;
    }

    queue<ll> q;
    fo(i, 26){
        if(trie[0].next[i] != -1){
            trie[trie[0].next[i]].fail = 0;
            q.push(trie[0].next[i]);
        }else trie[0].next[i] = 0;
    }

    while(!q.empty()){
        ll current = q.front(); 
        q.pop();
        fo(i, 26){
            if(trie[current].next[i] == -1){
                trie[current].next[i] = trie[trie[current].fail].next[i];
                continue;
            }
            ll child = trie[current].next[i];
            ll fail = trie[current].fail;
            while(trie[fail].next[i] == -1) fail = trie[fail].fail;
            trie[child].fail = trie[fail].next[i];
            trie[child].end |= trie[trie[child].fail].end;
            q.push(child);
        }
    }

    memo.assign(n+1, vl(trie.size(), -1));

    cout << dp(0, 0) << "\n";

    return 0;
}