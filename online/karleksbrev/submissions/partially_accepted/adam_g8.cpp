#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#include "karleksbrev.h"

#define sz(x) (ll)(x).size()

const int p = 31;
const int m = 1e9 + 9;

ll hashf(string s) {
    ll h = 0;
    ll pr = 1;
    for (auto ch: s) {
        h = (h + (ch - '0' + 1) * pr) % m;
        pr = (pr * p) % m;
    }

    return h;
}

string bin(ll n) {
    string s = "";
    for(ll i = 0; i < 51; i++) {
        s.push_back(((char)('0' + !!(n & (1ll << i)))));
    }

    return s;
}

string test;

string encode(string S)
{
    string E(100 - sz(S), '0'); 
    E += S;
    E += bin(hashf(E));
    test = E;

    assert(sz(E) == 151);

    return E;
}

/*
5 151
01011
1 3
*/

// Note: this is E after it has been corrupted
string decode(string E)
{
    for(ll i = 0; i < sz(E); i++) 
        for(ll j = i; j < sz(E); j++) {
            string cur;
            for(ll k = 0; k < i; k++)
                cur.push_back(E[k]);

            for(ll k = i; k <= j; k++)
                if(E[k] == '0')
                    cur.push_back('1');
                else 
                    cur.push_back('0');

            for(ll k = j + 1; k < sz(E); k++)
                cur.push_back(E[k]);

            assert(sz(cur) == 151);

            /*
            if(i == 1 && j == 3) {
                cout << "HELLO" << endl;
                cout << cur.substr(0, 100) << endl;
                cout << test.substr(0, 100) << endl;
                cout << bin(hashf(cur.substr(0, 100))) << endl;
                cout << cur.substr(100, 51) << endl;
                cout << test.substr(100, 51) << endl;
            }
            */

            string S = cur.substr(0, 100); 
            if(bin(hashf(S)) == cur.substr(100, 51))
                return S;
        }

    return "yoilo";
}
