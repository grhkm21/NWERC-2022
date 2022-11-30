#include <vector>
#include <iostream>
#include <queue>
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

struct matching {
	vector<vector<int>> adjlist;
	vector<int> pairs, dist;

	bool bfs(int n) {
		queue<int> q;
		for(int i = 0; i < n; i++) {
			if (pairs[i] < 0) {dist[i] = 0; q.push(i);}
			else dist[i] = -1;
		}
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for (int v : adjlist[u]) {
				if (pairs[v] < 0) return true;
				if (dist[pairs[v]] < 0) {
					dist[pairs[v]] = dist[u] + 1;
					q.push(pairs[v]);
		}}}
		return false;
	}

	bool dfs(int u) {
		for (int v : adjlist[u]) {
			if (pairs[v] < 0 ||
				 (dist[pairs[v]] > dist[u] && dfs(pairs[v]))) {
				pairs[v] = u; pairs[u] = v;
				return true;
		}}
		dist[u] = -1;
		return false;
	}

	int hopcroft_karp(int n) {
		int ans = 0;
		pairs.assign(sz(adjlist), -1);
		dist.resize(n);
		for (int i = 0; i < n; i++) for (int w : adjlist[i])
			if (pairs[w] < 0) {pairs[i] = w; pairs[w] = i; ans++; break;}
		while(bfs(n)) for(int i = 0; i < n; i++)
			if (pairs[i] < 0) ans += dfs(i);
		return ans;
	}
};

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

	matching r1;
	r1.adjlist = vector<vector<int>>(sz(le));

	fora(l, 26) {
		fora(x, lo[l]) {
			int t = sz(me);
			me.pb((char)(l + 'a'));
			fora(i, sz(le)) {
				if (forbidden[l][le[i]]) continue;
				while (sz(r1.adjlist) < sz(le) + t + 1) r1.adjlist.eb();
				r1.adjlist[i].pb(sz(le) + t);
				r1.adjlist[sz(le) + t].pb(i);
			}
		}
	}

	r1.hopcroft_karp(sz(le));

	fora(i, sz(le)) {
		if (r1.pairs[i] == -1) continue;
		char c = me[r1.pairs[i] - sz(le)];
		ans[le[i]] = c;
		--hi[c - 'a'];
	}

	matching r2;
	r2.adjlist = vector<vector<int>>(sz(le));

	int needed = n;
	fora(i, n) {
		if (ans[i] != '0') --needed;
	}

	fora(l, 26) {
		fora(x, hi[l]) {
			int t = sz(me);
			me.pb((char)(l + 'a'));
			fora(i, sz(le)) {
				if (ans[le[i]] != '0') continue;
				if (forbidden[l][le[i]]) continue;
				while (sz(r2.adjlist) < sz(le) + t + 1) r2.adjlist.eb();
				r2.adjlist[i].pb(sz(le) + t);
				r2.adjlist[sz(le) + t].pb(i);
			}
		}
	}

	r2.hopcroft_karp(sz(le));

	fora(i, sz(le)) {
		if (r2.pairs[i] == -1) continue;
		char c = me[r2.pairs[i] - sz(le)];
		ans[le[i]] = c;
		--hi[c - 'a'];
	}

	fora(i, n) {
		if (ans[i] == '0') {
			fora(l, 26) {
				if (!forbidden[l][i] && hi[l] > 0) {
					ans[i] = (char)(l + 'a');
					--hi[l];
				}
			}
		}
		if (ans[i] == '0') {
			fora(l, 26) {
				if (!forbidden[l][i]) {
					ans[i] = (char)(l + 'a');
					--hi[l];
				}
			}
		}
	}

	cout << ans << endl;
}
