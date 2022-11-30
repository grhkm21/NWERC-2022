#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool solve() {
	int m, n;
	cin >> m >> n;

	vector<vector<int>> adj(n);
	while (m--) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	for (auto &v: adj) {
		sort(begin(v), end(v));
		v.erase(unique(begin(v), end(v)), end(v));
	}

	for (int a = 0; a < n; a++) {
		int non_leaf_neighbors = 0;
		for (int b: adj[a]) {
			non_leaf_neighbors += b != a && size(adj[b]) > 1;
		}
		if (non_leaf_neighbors > 2) return false;
	}

	int C = 0;
	vector<int> comp(n,-1);
	for (int a = 0; a < n; a++) if (comp[a] == -1) {
		auto dfs = [&](const auto &self, int b) -> void {
			comp[b] = C;
			for (int c: adj[b]) {
				if (comp[c] == -1) self(self, c);
			}
		};
		dfs(dfs, a);
		C++;
	}

	vector<int> node_count(C), edge_count(C), loop_count(C);
	for (int a = 0; a < n; a++) {
		node_count[comp[a]]++;
		for (int b: adj[a]) {
			edge_count[comp[a]] += a < b;
			loop_count[comp[a]] += a == b;
		}
	}

	int singles = 0, chains = 0, circles = 0;
	for (int k = 0; k < C; k++) {
		if (edge_count[k] + loop_count[k] == 0) singles++;
		else if (edge_count[k] < node_count[k]) chains++;
		else circles++;
	}
	return circles == 0 || (circles == 1 && chains == 0);
}

int main() {
	cout << (solve() ? "possible" : "impossible") << '\n';
}
