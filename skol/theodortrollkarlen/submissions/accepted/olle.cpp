using namespace std;
#include <bits/stdc++.h>

#define rep(i,a,b) for (int i = a; i < b; i++)
#define pb push_back

typedef long long ll;
typedef vector<ll> vi;

const ll mod = 1000000007;
const ll maxn = 200100;

ll euclid(ll a, ll b, ll &x, ll &y) {
	if (!b) return x = 1, y = 0, a;
	ll d = euclid(b, a % b, y, x);
	return y -= a/b * x, d;
}

struct Mod {
	ll x;
	Mod(ll xx) : x(xx%mod) {}
	Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
	Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
	Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
	Mod operator/(Mod b) { return *this * invert(b); }
	Mod invert(Mod a) {
		ll x, y, g = euclid(a.x, mod, x, y);
		assert(g == 1); return Mod((x + mod) % mod);
	}
	Mod operator^(ll e) {
		if (!e) return Mod(1);
		Mod r = *this ^ (e / 2); r = r * r;
		return e&1 ? *this * r : r;
	}
};

ostream& operator<<(ostream& os, const Mod& m)
{
    os << (m.x + mod) % mod;
    return os;
}

vector<Mod> factorial, p2;

void calc() {
    factorial.push_back(Mod(1));
    for (ll x = 1; x < maxn; x++) {
        factorial.push_back(factorial[x - 1] * Mod(x));
    }
    p2.push_back(Mod(1));
    for (ll x = 1; x < maxn; x++) {
        p2.push_back(p2[x - 1] * Mod(2));
    }
}

Mod choose(Mod n, Mod k) {
    return factorial[n.x] / (factorial[(n-k).x] * factorial[k.x]);
}

Mod pow(Mod n, Mod k) {
    Mod ans = Mod(1);
    Mod N = Mod(n);
    rep(i,0,30) {
        if (k.x & (1<<i)) ans = ans * N;
        N = N * N;
    }
    return ans;
}

ll n, k, s, a;

Mod amnt(ll K) {
    // how many ways to win in <= K rounds?

    Mod ans = Mod(0);

    // iterate over how many have more than a*K

    for (ll i = 0; i <= min(K,n); i++) {
        Mod res = choose(Mod(n), Mod(i));

        res = res * pow(Mod(a * K), Mod(n - i));

        res = res * choose(Mod(K), Mod(i));

        res = res * pow(Mod(s), Mod(i));

        ans = ans + res;    
    }

    return ans;
}

int main() {
    calc();
    cin >> n >> k >> s >> a;

    if (k == 0) {
        cout << 1 << endl;
        exit(0);
    }
    
    cout << amnt(k) - amnt(k-1) << endl;
}