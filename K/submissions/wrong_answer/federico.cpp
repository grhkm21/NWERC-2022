#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	ll m, n;
	cin >> m >> n;
	vector<set<ll>> adj(n);	//no multi edges
	for (ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		a--;
		b--;
		adj[a].insert(b);
		adj[b].insert(a);
	}

	//delete all leafes (~~keep vertex with selfloop~~ and component with single edge)
	vector<bool> deleted(n);
	for (ll i = 0; i < n; i++) {
		if (adj[i].empty()) {
			deleted[i] = true;
		} else if (sz(adj[i]) == 1) {
			ll j = *(adj[i].begin());
			if (/*i != j &&*/ !deleted[j]) deleted[i] = true;
		}
	}

	//count some properties of the graph with dfs
	ll components = 0;
	ll cycles = 0;
	ll maxDegree = 0;
	vector<bool> seen(n);
	for (ll i = 0; i < n; i++) {
		if (seen[i] || deleted[i]) continue;
		components++;
		vector<ll> stack = {i};
		seen[i] = true;
		bool hasLeaf = false;
		while (!stack.empty()) {
			ll c = stack.back();
			stack.pop_back();
			ll deg = 0;
			for (ll x : adj[c]) {
				if (!deleted[x] && x != c) deg++;
				if (!deleted[x] && !seen[x]) {
					seen[x] = true;
					stack.push_back(x);
				}
			}
			maxDegree = max(maxDegree, deg);
			hasLeaf |= deg <= 1;
		}
		if (!hasLeaf) cycles++;
	}

	if (maxDegree > 2) cout << "impossible" << endl;
	else if (cycles > 1) cout << "impossible" << endl;
	else if (cycles == 1 && components > 1) cout << "impossible" << endl;
	else cout << "possible" << endl;
}