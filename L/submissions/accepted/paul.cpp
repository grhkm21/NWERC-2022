#include <iostream>
#include <vector>
using namespace std;
using i64 = long long;

const i64 oo = 0x3f3f3f3f3f3f3f3f;
struct flow_network {
	struct edge { int to; i64 cap; };
	
	int n, s, t;
	vector<bool> mark;
	vector<vector<int>> adj;
	vector<edge> e;

	flow_network(int n, int s, int t): n(n), s(s), t(t), adj(n) { }

	void add_edge(int a, int b, i64 c) {
		adj[a].push_back(e.size());
		e.push_back({b,c});
		adj[b].push_back(e.size());
		e.push_back({a,0});
	}
	
	i64 dfs(int i, i64 cap, i64 delta) {
		if (i == t) return cap;
		if (mark[i]) return 0;
		mark[i] = true;
		for (int j: adj[i]) if (e[j].cap >= delta) {
			if (i64 c = dfs(e[j].to, min(cap,e[j].cap), delta)) {
				e[j].cap -= c, e[j^1].cap += c;
				return c;
			}
		}
		return 0;
	}

	i64 max_flow() {
		i64 flow = 0, delta = oo;
		while (delta > 0) {
			mark.assign(n, 0);
			i64 c = dfs(s, oo, delta);
			if (c > 0) flow += c; else delta /= 2;
		}
		return flow;
	}
};

int main() {
	int m, n;
	cin >> m >> n;

	vector<int> min_count(26), max_count(26, n);
	vector<int> mask(n, (1 << 26) - 1);
	for (int i = 0; i < m-1; i++) {
		string s, t;
		cin >> s >> t;

		vector<int> count(26);
		vector<bool> has_black(26);
		for (int i = 0; i < n; i++) {
			int k = s[i]-'a';
			if (t[i] == 'G') {
				mask[i] &= 1 << k;
				count[k]++;
			} else if (t[i] == 'Y') {
				mask[i] &= ~(1 << k);
				count[k]++;
			} else {
				mask[i] &= ~(1 << k);
				has_black[k] = 1;
			}
		}

		for (int k = 0; k < 26; k++) {
			min_count[k] = max(min_count[k], count[k]);
			if (has_black[k]) max_count[k] = count[k];
		}
	}

	int N = n+29, s = N-3, t = N-2, u = N-1;
	flow_network F(N, s, t);
	int rem = n;
	for (int k = 0; k < 26; k++) {
		F.add_edge(s, n+k, min_count[k]);
		F.add_edge(u, n+k, max_count[k]-min_count[k]);
		rem -= min_count[k];
	}
	F.add_edge(s, u, rem);
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < 26; k++) {
			if (mask[i] & (1 << k)) F.add_edge(n+k, i, 1);
		}
		F.add_edge(i, t, 1);
	}

	if (F.max_flow() < n) {
		cout << "impossible" << endl;
	} else {
		string res(n, 'a');
		for (int i = 0; i < n; i++) {
			for (int j: F.adj[i]) {
				if (F.e[j].cap) res[i] += F.e[j].to - n;
			}
		}
		cout << res << endl;
	}
}
