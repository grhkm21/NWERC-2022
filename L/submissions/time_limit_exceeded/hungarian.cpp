#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
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

using ll = int;
using ld = long double;

constexpr ll M = 1;
constexpr ll MM = 1000;
constexpr ll INF = MM * MM;

constexpr ll N = 500;

ll costs[N][26 * N];

vector<int> xy;

void hungarian(int l, int r) {
	vector<ll> lx(l), ly(r);
	xy = vector<int>(l, -1);
	vector<int> yx(r, -1), augmenting(r);
	vector<bool> s(l);
	vector<pair<ll, int>> slack(r);

	for (int x = 0; x < l; x++)
		lx[x] = *max_element(costs[x], costs[x] + r);
	for (int root = 0; root < l; root++) {
		augmenting.assign(r, -1);
		s.assign(l, false);
		s[root] = true;
		for (int y = 0; y < r; y++) {
			slack[y] = {lx[root] + ly[y] - costs[root][y], root};
		}
		int y = -1;
		while (true) {
			ll delta = INF;
			int x = -1;
			for (int yy = 0; yy < r; yy++) {
				if (augmenting[yy] < 0) {
					if (slack[yy].first < delta) {
						delta = slack[yy].first;
						x = slack[yy].second;
						y = yy;
			}}}
			if (delta > 0) {
				for (int x = 0; x < l; x++) if (s[x]) lx[x] -= delta;
				for (int y = 0; y < r; y++) {
					if (augmenting[y] >= 0) ly[y] += delta;
					else slack[y].first -= delta;
			}}
			augmenting[y] = x;
			x = yx[y];
			if (x == -1) break;
			s[x] = true;
			for (int y = 0; y < r; y++) {
				if (augmenting[y] < 0) {
					ll alt = lx[x] + ly[y] - costs[x][y];
					if (slack[y].first > alt) {
						slack[y] = {alt, x};
		}}}}
		while (y >= 0) {
			int x = augmenting[y];
			int prec = xy[x];
			yx[y] = x;
			xy[x] = y;
			y = prec;
	}}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	cin >> m >> n;

	--m;

	vector<vector<bool>> forced(26, vector<bool>(n));
	vector<vector<bool>> forbidden(26, vector<bool>(n));
	vector<int> lo(26), hi(26, n);

	fora(_, m) {
		string s, t;
		cin >> s >> t;

		vector<int> gy(26), b(26);
		vector<bool> seen(26);
		fora(i, n) {
			int l = s[i] - 'a';

			if (t[i] == 'G') {
				++gy[l];
				forced[l][i] = true;
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

	string ans(n, '0');
	fora(i, n) fora(l, 26) {
		if (forced[l][i]) {
			ans[i] = (char)(l + 'a');
			--lo[l];
			--hi[l];
		}
	}

	vector<char> me;
	vector<int> le;

	fora(i, n) {
		if (ans[i] == '0') {
			le.pb(i);
		}
	}

	fora(l, 26) {
		fora(x, hi[l]) {
			int t = sz(me);
			me.pb((char)(l + 'a'));
			fora(i, sz(le)) {
				if (forbidden[l][le[i]]) continue;
				costs[i][t] = x < lo[l] ? MM : M;
			}
		}
	}

	hungarian(sz(le), sz(me));

	fora(i, sz(le)) {
		ans[le[i]] = me[xy[i]];
	}
	cout << ans << endl;
}
