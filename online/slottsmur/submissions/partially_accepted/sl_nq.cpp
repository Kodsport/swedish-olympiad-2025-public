#include <bits/stdc++.h>
using namespace std;

#define rep(i,f,t) for (int i = (f); i < (t); i++)
#define all(x) (x).begin(), (x).end()
#define trav(a,x) for (auto& a : x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Tree {
	typedef pair<int, int> T;
	static constexpr T unit = {INT_MIN, INT_MIN};
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int readint() {
	int x;
	cin >> x;
	return x;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N = readint();
	int Q = readint();
	vi v(N);
	rep(i,0,N) v[i] = readint();
	Tree st(N);
	rep(i,0,N) st.update(i, {v[i], i});
	rep(qi,0,Q) {
		int t = readint();
		if (t == 1) {
			int l = readint(), r = readint();
			--l;
			int maxi = st.query(l, r).second;
			int level = 0;
			ll res = 0;
			rep(i,l,maxi) {
				level = max(level, v[i]);
				res += level - v[i];
			}
			level = 0;
			for (int i = r-1; i > maxi; i--) {
				level = max(level, v[i]);
				res += level - v[i];
			}
			cout << res << '\n';
		} else {
			int i = readint(), w = readint();
			--i;
			v[i] += w;
			st.update(i, {v[i], i});
		}
	}
}
