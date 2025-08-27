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


string hashing(string x){ 
    ll out = 0;
    for(char c : x){
        out = (out*131ll+vl{63289, 1731}[c-'0'])%INF;
    }
    return bitset<32>(out).to_string();
}

string encode(string x){
    return x+hashing(x);
}

string fliping(string x, int i, int j){
    fo(k, j){
        if(x[i+k] == '0') x[i+k] = '1';
        else x[i+k] = '0';
    }
    return x;
}

string decode(string x){
    fo(i, 132){
        for(ll j = 1; j<=132-i; j++){
            string temp = fliping(x, i, j);
            if(hashing(temp.substr(0, 100)) == temp.substr(100, 32)){
                return temp.substr(0, 100);
            }
        }
    }
    return "ahop";
}
