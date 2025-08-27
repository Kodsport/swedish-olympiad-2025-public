#include <bits/stdc++.h>
#pragma GCC target ("avx2")
#pragma GCC optimize ("O3")
#include <immintrin.h>
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

const int SIMD = 8;
const int chunksize = 1 << 10;
const int subchunksize = chunksize / SIMD;

unsigned tr(unsigned i) {
	unsigned j = i % chunksize;
	i -= j;
	j = (j / subchunksize) + (j % subchunksize) * SIMD;
	i += j;
	return i;
}

struct Solver {
	int N;
	vi v;
	Tree st;
	int* chunks;
	vi maxs;

	Solver(vi& v) : N(sz(v)), v(v), st(N) {
		rep(i,0,N) st.update(i, {v[i], i});
		chunks = (int*)_mm_malloc((N + chunksize) * 4, 32);
		rep(i,0,N+chunksize) chunks[i] = INT_MAX;
		rep(i,0,N) chunks[tr(i)] = v[i];
		maxs.assign(N / subchunksize + 1, -1);
	}

	void update(int i, int w) {
		v[i] += w;
		chunks[tr(i)] += w;
		st.update(i, {v[i], i});
		maxs[i / subchunksize] = -1;
	}

	ll solve2(int start, int &ma, int blockstart, int l, int r) {
		ll res = 0;
		if (l == blockstart && r - l == chunksize) {
			int* chunk = &chunks[blockstart];
			alignas(32) int levels[SIMD];
			rep(j,0,SIMD) {
				levels[j] = ma;
				int k = l / subchunksize + j;
				if (maxs[k] == -1) maxs[k] = st.query(l + subchunksize*j, l + subchunksize*(j+1)).first;
				ma = max(ma, maxs[k]);
			}
			/*
			rep(j,0,SIMD) {
				rep(i,0,subchunksize) {
					int x = v[l + subchunksize*j + i];
					levels[j] = max(levels[j], x);
					res += levels[j] - x;
				}
			}
			return res;
			*/
			__m256i level = _mm256_load_si256((__m256i*)levels);
			__m256i acc = _mm256_set1_epi32(INT_MIN), acc2{};
			rep(i,0,subchunksize) {
				__m256i v = _mm256_load_si256((__m256i*)&chunk[i*SIMD]);
				level = _mm256_max_epi32(level, v);
				__m256i add = _mm256_sub_epi32(level, v);
				__m256i nacc = _mm256_add_epi32(acc, add);
				acc2 = _mm256_sub_epi32(acc2, _mm256_cmpgt_epi32(acc, nacc));
				acc = nacc;
			}
			alignas(32) int accs[SIMD], accs2[SIMD];
			_mm256_store_si256((__m256i*)accs, acc);
			_mm256_store_si256((__m256i*)accs2, acc2);
			rep(i,0,SIMD) {
				res += (unsigned)accs[i] - (unsigned)INT_MIN;
				res += (ll)accs2[i] << 32;
			}
		} else {
			int level = ma;
			rep(i,l,r) {
				level = max(level, v[i]);
				res += level - v[i];
			}
			ma = level;
		}
		return res;
	}

	ll solve(int l, int r) {
		ll res = 0;
		int ma = INT_MIN;
		for (int i = 0; i < N; i += chunksize) {
			int j = i + chunksize;
			int i2 = max(l, i);
			int j2 = min(r, j);
			if (i2 >= j2) continue;
			res += solve2(l, ma, i, i2, j2);
		}
		return res;
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
	vi v(N), vr(N);
	rep(i,0,N) v[i] = readint();
	rep(i,0,N) vr[i] = v[N-1-i];

	Solver s(v);
	Solver rs(vr);

	rep(qi,0,Q) {
		int t = readint();
		if (t == 1) {
			int l = readint(), r = readint();
			--l;
			int maxi = s.st.query(l, r).second;
			ll res = s.solve(l, maxi) + rs.solve(N-r, N-1-maxi);
			cout << res << '\n';
		} else {
			int i = readint(), w = readint();
			--i;
			s.update(i, w);
			rs.update(N-1-i, w);
		}
	}
}
