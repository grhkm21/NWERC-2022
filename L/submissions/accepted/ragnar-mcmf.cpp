#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

using ll = long long;
using vi = vector<ll>;
ll LLINF = 1e9;
using F  = ll;
using W  = ll; // types for flow and weight/cost
struct S {
	const int v;  // neighbour
	const int r;  // index of the reverse edge
	F f;          // current flow
	const F cap;  // capacity
	const W cost; // unit cost
	S(int v, int ri, F c, W cost = 0) : v(v), r(ri), f(0), cap(c), cost(cost) {}
	inline F res() const { return cap - f; }
};
struct FlowGraph : vector<vector<S>> {
	FlowGraph(size_t n) : vector<vector<S>>(n) {}
	void add_edge(int u, int v, F c, W cost = 0) {
		auto& t = *this;
		t[u].emplace_back(v, t[v].size(), c, cost);
		t[v].emplace_back(u, t[u].size() - 1, c, -cost);
	}
	void add_arc(int u, int v, F c, W cost = 0) {
		auto& t = *this;
		t[u].emplace_back(v, t[v].size(), c, cost);
		t[v].emplace_back(u, t[u].size() - 1, 0, -cost);
	}
	void clear() {
		for(auto& E : *this)
			for(auto& e : E) e.f = 0LL;
	}
};

using F = ll;
using W = ll;
W WINF  = LLINF;
F FINF  = LLINF;
struct Q {
	int u;
	F c;
	W w;
}; // target, maxflow and total cost/weight
bool operator>(const Q& l, const Q& r) {
	return l.w > r.w;
}
struct Edmonds_Karp_Dijkstra {
	FlowGraph& g;
	int V, s, t;
	vector<W> pot;
	Edmonds_Karp_Dijkstra(FlowGraph& g, int s, int t) : g(g), V(g.size()), s(s), t(t), pot(V) {}
	pair<F, W> run() { // return pair<f, cost>
		F maxflow = 0;
		W cost    = 0; // Bellmann-Ford for potentials
		fill(pot.begin(), pot.end(), WINF);
		pot[s] = 0;
		for(int i = 0; i < V - 1; ++i) {
			bool relax = false;
			for(int u = 0; u < V; ++u)
				if(pot[u] != WINF)
					for(auto& e : g[u])
						if(e.cap > e.f)
							if(pot[u] + e.cost < pot[e.v]) pot[e.v] = pot[u] + e.cost, relax = true;
			if(!relax) break;
		}
		for(int u = 0; u < V; ++u)
			if(pot[u] == WINF) pot[u] = 0;
		while(true) {
			priority_queue<Q, vector<Q>, greater<Q>> q;
			vector<vector<S>::iterator> p(V, g.front().end());
			vector<W> dist(V, WINF);
			F f, tf = -1;
			q.push({s, FINF, 0});
			dist[s] = 0;
			while(!q.empty()) {
				int u = q.top().u;
				W w   = q.top().w;
				f     = q.top().c;
				q.pop();
				if(w != dist[u]) continue;
				if(u == t && tf < 0) tf = f;
				for(auto it = g[u].begin(); it != g[u].end(); it++) {
					auto& e = *it;
					W d     = w + e.cost + pot[u] - pot[e.v];
					if(e.cap > e.f && d < dist[e.v]) {
						q.push({e.v, min(f, e.cap - e.f), dist[e.v] = d});
						p[e.v] = it;
					}
				}
			}
			auto it = p[t];
			if(it == g.front().end()) return {maxflow, cost};
			maxflow += f = tf;
			while(it != g.front().end()) {
				auto& r = g[it->v][it->r];
				cost += f * it->cost;
				it->f += f;
				r.f -= f;
				it = p[r.v];
			}
			for(int u = 0; u < V; ++u)
				if(dist[u] != WINF) pot[u] += dist[u];
		}
	}
};

int main() {
	int n, l;
	cin >> n >> l;
	--n;
	// For green positions: 1 edge of cost -1 to the end
	string green(l, ' ');
	vector<vector<bool>> pos(26, vector<bool>(l, true));
	// Min number of Y/G at the same time for this char.
	vector<int> min_cnt(26, 0);
	// If not all of this char were Y/G, the max cnt is also known.
	vector<int> max_cnt(26, l);
	for(int g = 0; g < n; ++g) {
		string guess, reply;
		cin >> guess >> reply;
		// Greens
		for(int i = 0; i < l; ++i)
			if(reply[i] == 'G') green[i] = guess[i];
		for(int c = 0; c < 26; ++c) {
			// count
			int cnt         = 0;
			bool all_marked = true;
			for(int i = 0; i < l; ++i) {
				if(guess[i] - 'a' == c) {
					if(reply[i] == 'B') {
						all_marked = false;
					} else {
						++cnt;
					}
				}
			}
			min_cnt[c] = max(min_cnt[c], cnt);
			if(!all_marked) {
				max_cnt[c] = cnt;
			}
			// positions:
			// remove all positions where c occurs without G
			for(int i = 0; i < l; ++i) {
				if(guess[i] - 'a' == c && reply[i] != 'G') {
					pos[c][i] = false;
				}
			}
		}
	}

	// a..z, 0..l-1, s, t
	FlowGraph g(l + 28);
	int s = 26 + l;
	int t = 26 + l + 1;
	// cap-1 free edge from each pos to end
	for(int i = 0; i < l; ++i) g.add_arc(26 + i, t, 1);
	// min_cnt free edge from start to each char
	for(int c = 0; c < 26; ++c) g.add_arc(s, c, min_cnt[c], 0);
	// max_cnt-min_cnt payed edge from start to each char
	for(int c = 0; c < 26; ++c) g.add_arc(s, c, max_cnt[c] - min_cnt[c], 1);
	int target_cost = l;
	for(int c = 0; c < 26; ++c) {
		target_cost -= min_cnt[c];
	}

	// Add char-pos edges:
	for(int i = 0; i < l; ++i) {
		// For green positions, add a single incoming edge.
		if(green[i] != ' ') {
			g.add_arc(green[i] - 'a', 26 + i, 1);
		} else {
			// For other positions, add an edge from each possible incoming char.
			for(int c = 0; c < 26; ++c) {
				if(pos[c][i]) g.add_arc(c, 26 + i, 1);
			}
		}
	}
	auto [flow, cost] = Edmonds_Karp_Dijkstra(g, s, t).run();
	assert(cost == target_cost);
	assert(flow == l);

	// Find optimal flow edges.
	string ans(l, ' ');
	for(int i = 0; i < l; ++i) {
		for(S& edge : g[26 + i]) {
			if(edge.v < 26 && edge.f == -1) {
				ans[i] = char('a' + edge.v);
			}
		}
	}
	cout << ans << endl;
}
