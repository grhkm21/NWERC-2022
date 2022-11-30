#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

using ll = long long;
using vi = vector<ll>;
ll INF   = 1e9;
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

struct Dinic {
	FlowGraph& edges;
	int V, s, t;
	vi l;
	vector<vector<S>::iterator> its; // levels and iterators
	Dinic(FlowGraph& edges, int s, int t)
	    : edges(edges), V(edges.size()), s(s), t(t), l(V, -1), its(V) {}
	ll augment(int u, F c) { // we reuse the same iterators
		if(u == t) return c;
		ll r = 0LL;
		for(auto& i = its[u]; i != edges[u].end(); i++) {
			auto& e = *i;
			if(e.res() && l[u] < l[e.v]) {
				auto d = augment(e.v, min(c, e.res()));
				if(d > 0) {
					e.f += d;
					edges[e.v][e.r].f -= d;
					c -= d;
					r += d;
					if(!c) break;
				}
			}
		}
		return r;
	}
	ll run() {
		ll flow = 0, f;
		while(true) {
			fill(l.begin(), l.end(), -1);
			l[s] = 0; // recalculate the layers
			queue<int> q;
			q.push(s);
			while(!q.empty()) {
				auto u = q.front();
				q.pop();
				its[u] = edges[u].begin();
				for(auto&& e : edges[u])
					if(e.res() && l[e.v] < 0) l[e.v] = l[u] + 1, q.push(e.v);
			}
			if(l[t] < 0) return flow;
			while((f = augment(s, INF)) > 0) flow += f;
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

	// a..z, 0..l-1, s, s2, t
	FlowGraph g(26 + l + 3);
	int s  = 26 + l;
	int s2 = 26 + l + 1;
	int t  = 26 + l + 2;
	// cap-1 free edge from each pos to end
	for(int i = 0; i < l; ++i) g.add_arc(26 + i, t, 1);
	// min_cnt free edge from start to each char
	int free_cnt = l;
	for(int c = 0; c < 26; ++c) {
		g.add_arc(s, c, min_cnt[c]);
		free_cnt -= min_cnt[c];
	}
	// free_cnt edge from s to s2
	g.add_arc(s, s2, free_cnt);
	// edges relaxed from s2 to chars
	for(int c = 0; c < 26; ++c) g.add_arc(s2, c, max_cnt[c] - min_cnt[c]);

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
	auto flow = Dinic(g, s, t).run();
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
	cerr << ans << endl;
	cout << ans << endl;
}
