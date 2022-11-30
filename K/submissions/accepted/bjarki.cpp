#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, k;
	cin >> n >> k;
	vector<vector<int> > adj(k);
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		a--, b--;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	vector<bool> critical(k);
	for (int i = 0; i < k; i++) {
		set<int> neigh(adj[i].begin(), adj[i].end());
		critical[i] = neigh.find(i) != neigh.end() || neigh.size() > 1;
	}
	vector<bool> visited(k);
	int cycles = 0;
	int paths = 0;
	for (int i = 0; i < k; i++) {
		if (visited[i] || !critical[i]) continue;
		stack<int> S;
		S.push(i);
		visited[i] = true;
		bool is_cycle = true;
		while (!S.empty()) {
			int cur = S.top();
			S.pop();
			set<int> cur_adj;
			for (auto nxt : adj[cur]) {
				if (critical[nxt] && nxt != cur) {
					cur_adj.insert(nxt);
				}
			}
			if (cur_adj.size() > 2) {
				cout << "impossible" << endl;
				return 0;
			}
			if (cur_adj.size() <= 1) {
				is_cycle = false;
			}
			for (auto nxt : cur_adj) {
				if (!visited[nxt]) {
					S.push(nxt);
					visited[nxt] = true;
				}
			}
		}
		if (is_cycle) {
			cycles++;
		} else {
			paths++;
		}
	}
	if (cycles == 1) {
		for (int i = 0; i < k; i++) {
			for (auto v : adj[i]) {
				if (!critical[i] && !critical[v]) {
					cout << "impossible" << endl;
					return 0;
				}
			}
		}
		if (paths == 0) {
			cout << "possible" << endl;
			return 0;
		}
		cout << "impossible" << endl;
		return 0;
	}
	if (cycles > 1) {
		cout << "impossible" << endl;
		return 0;
	}
	cout << "possible" << endl;
	return 0;
}
