#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

#define pb push_back
#define mp make_pair
#define eb emplace_back
#define all(a) begin(a), end(a)
#define has(a, b) (a.find(b) != a.end())
#define fora(i, n) for(int i = 0; i < n; i++)
#define forb(i, n) for(int i = 1; i <= n; i++)
#define forc(a, b) for(const auto &a : b)
#define ford(i, n) for(int i = n; i >= 0; i--)
#define maxval(t) numeric_limits<t>::max()
#define minval(t) numeric_limits<t>::min()
#define imin(a, b) a = min(a, b)
#define imax(a, b) a = max(a, b)
#define sz(x) (int)(x).size()
#define pvec(v) copy(all(v), ostream_iterator<decltype(v)::value_type>(cout, " "))

#define dbgs(x) #x << " = " << x
#define dbgs2(x, y) dbgs(x) << ", " << dbgs(y)
#define dbgs3(x, y, z) dbgs2(x, y) << ", " << dbgs(z)
#define dbgs4(w, x, y, z) dbgs3(w, x, y) << ", " << dbgs(z)

using ll = long long;
using ld = long double;

string ans;
vector<ll> lo, hi;
vector<vector<bool>> forbidden;
vector<bool> forced;
int n, m;
mt19937 rng(43);

bool choose(int i, int c);

bool backtrack(int i) {
	if (i == n) {
		fora(c, 26) {
			if (lo[c] > 0) {
				return false;
			}
		}
		return true;
	}

	if (forced[i]) return backtrack(i + 1);
	vector<bool> done(26);

	vector<int> valid;

	fora(c, 26) {
		if (lo[c] <= 0) continue;
		if (hi[c] == 0) continue;
		if (forbidden[c][i]) continue;
		done[c] = true;
		valid.pb(c);
	}

	shuffle(all(valid), rng);
	forc(c, valid) {
		if (choose(i, c)) {
			return true;
		}
	}

	valid.clear();

	fora(c, 26) {
		if (done[c]) continue;
		if (forbidden[c][i]) continue;
		if (hi[c] == 0) continue;
		valid.pb(c);
	}

	shuffle(all(valid), rng);
	forc(c, valid) {
		if (choose(i, c)) {
			return true;
		}
	}

	return false;
}

bool choose(int i, int c) {
	ans[i] = (char)(c + 'a');
	--lo[c];
	--hi[c];
	bool res = backtrack(i + 1);
	++lo[c];
	++hi[c];
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> m >> n;


	vector<int> perm(n);
	iota(all(perm), 0);

	shuffle(all(perm), rng);

	vector<int> inv(n);

	fora(i, n) {
		inv[perm[i]] = i;
	}

	--m;

	ans = string(n, '0');

	forced = vector<bool>(n);
	forbidden = vector<vector<bool>>(26, vector<bool>(n));
	lo = vector<ll>(26);
	hi = vector<ll>(26, n);

	fora(_, m) {
		string ss, tt;
		cin >> ss >> tt;

		string s(n, '0'), t(n, '0');
		fora(i, n) {
			s[i] = ss[perm[i]];
			t[i] = tt[perm[i]];
		}

		vector<ll> gy(26), b(26);
		vector<bool> seen(26);
		fora(i, n) {
			int l = s[i] - 'a';

			if (t[i] == 'G') {
				++gy[l];
				ans[i] = s[i];
				forced[i] = true;
			} else if (t[i] == 'Y') {
				++gy[l];
				forbidden[l][i] = true;
			} else {
				++b[l];
				forbidden[l][i] = true;
			}
		}

		fora(l, 26) {
			imax(lo[l], gy[l]);
			if (b[l] > 0) {
				imin(hi[l], gy[l]);
			}
		}
	}

	fora(i, n) {
		if (forced[i]) {
			int l = ans[i] - 'a';
			--lo[l];
			--hi[l];
		}
	}

	backtrack(0);

	string aans(n, '0');
	fora(i, n) aans[i] = ans[inv[i]];

	cout << aans << endl;
}
