#include <iostream>
#include <set>
#include <vector>
using namespace std;
using i64 = long long;

const i64 oo = 0x3f3f3f3f3f3f3f3f;
struct flow_network {
	struct edge { int to; i64 cap, cost; };

	int n, s, t;
	vector<vector<int>> adj;
	vector<edge> e;
	
	flow_network(int n, int s, int t): n(n), s(s), t(t), adj(n) { }

	void add_edge(int a, int b, i64 cap, i64 cost) {
		adj[a].push_back(size(e));
		e.push_back({b,cap,cost});
		adj[b].push_back(size(e));
		e.push_back({a,0,-cost});
	}

	pair<i64,i64> mcmf() {
		vector<i64> pot(n);
		for (int t = 0; t < n; t++) {
			for (int i = 0; i < n; i++) {
				for (int k: adj[i]) if (e[k].cap) {
					pot[e[k].to] = min(pot[e[k].to],pot[i] + e[k].cost);
				}
			}
		}
		i64 flow = 0, cost = 0;
		while (true) {
			vector<i64> dist(n,oo);
			vector<int> pred(n);
			set<pair<i64,int>> q;
			dist[s] = 0, q.insert({0,s});
			while (!q.empty()) {
				int i = begin(q)->second;
				q.erase(begin(q));
				for (int k: adj[i]) if (e[k].cap) {
					int j = e[k].to, ndist = dist[i] + e[k].cost + pot[i] - pot[j];
					if (ndist >= dist[j]) continue;
					q.erase({dist[j],j});
					dist[j] = ndist, pred[j] = k;
					q.insert({dist[j],j});
				}
			}
			if (dist[t] == oo) break;

			i64 cap = oo, cost1 = 0;
			for (int i = t; i != s; i = e[pred[i]^1].to) {
				cap = min(cap,e[pred[i]].cap), cost1 += e[pred[i]].cost;
			}
			flow += cap, cost += cap*cost1;
			for (int i = t; i != s; i = e[pred[i]^1].to) {
				e[pred[i]].cap -= cap, e[pred[i]^1].cap += cap;
			}
			for (int i = 0; i < n; i++) {
				pot[i] += dist[i];
			}
		}
		return {flow,cost};
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

	int N = n+28, s = N-2, t = N-1;
	flow_network F(N, s, t);
	for (int k = 0; k < 26; k++) {
		F.add_edge(s, n+k, min_count[k], 1);
		F.add_edge(s, n+k, max_count[k]-min_count[k], 1e9);
	}
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < 26; k++) {
			if (mask[i] & (1 << k)) F.add_edge(n+k, i, 1, 0);
		}
		F.add_edge(i, t, 1, 0);
	}

	if (F.mcmf().first < n) {
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
