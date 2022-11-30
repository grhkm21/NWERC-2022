#include <bits/stdc++.h>
using namespace std;

const int INF = 2147483647;

#define MAXV 2000
int q[MAXV], p[MAXV], d[MAXV];
struct flow_network {
  struct edge { int v, nxt, cap;
    edge(int _v, int _cap, int _nxt)
      : v(_v), nxt(_nxt), cap(_cap) { } };
  int n, *head; vector<edge> e, e_store;
  flow_network(int _n) : n(_n) {
    memset(head = new int[n], -1, n*sizeof(int)); }
  void reset() { e = e_store; }
  void add_edge(int u, int v, int uv, int vu=0) {
    e.push_back(edge(v,uv,head[u])); head[u]=(int)size(e)-1;
    e.push_back(edge(u,vu,head[v])); head[v]=(int)size(e)-1;}
  int max_flow(int s, int t, bool res=true) {
    e_store = e;
    int l, r, v, f = 0;
    while (true) {
      memset(d, -1, n*sizeof(int));
      memset(p, -1, n*sizeof(int));
      l = r = 0, d[q[r++] = s] = 0;
      while (l < r)
        for (int u = q[l++], i = head[u]; i != -1; i=e[i].nxt)
          if (e[i].cap > 0 &&
              (d[v = e[i].v] == -1 || d[u] + 1 < d[v]))
            d[v] = d[u] + 1, p[q[r++] = v] = i;
      if (p[t] == -1) break;
      int at = p[t], x = INF;
      while (at != -1)
        x = min(x, e[at].cap), at = p[e[at^1].v];
      at = p[t], f += x;
      while (at != -1)
        e[at].cap -= x, e[at^1].cap += x, at = p[e[at^1].v]; }
    if (res) reset();
    return f; } };

int main() {
	int m, n;
	cin >> m >> n;
	vector<char> found(n, 0);
	vector<set<char>> forbidden(n);
	map<char,int> occurrences, used;
	set<char> fixed;
	vector<string> guesses, patterns;
	for (int i = 0; i < m-1; i++) {
		string guess, pattern;
		cin >> guess >> pattern;
		guesses.push_back(guess);
		patterns.push_back(pattern);
		for (int j = 0; j < n; j++) {
			if (pattern[j] == 'G') {
				found[j] = guess[j];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (found[i]) {
			used[found[i]]++;
		}
	}
	for (int i = 0; i < m-1; i++) {
		string guess = guesses[i],
		       pattern = patterns[i];
		map<char,int> yellows;
		for (int j = 0; j < n; j++) {
			if (pattern[j] == 'G') {
				yellows[guess[j]]++;
			} else if (pattern[j] == 'Y') {
				forbidden[j].insert(guess[j]);
				yellows[guess[j]]++;
			} else {
				forbidden[j].insert(guess[j]);
				fixed.insert(guess[j]);
			}
		}
		for (auto ys : yellows) {
			occurrences[ys.first] = max(occurrences[ys.first], ys.second - used[ys.first]);
		}
	}
	for (auto f : fixed) {
		occurrences[f] = max(occurrences[f], 0);
	}
	vector<char> letters;
	for (auto occ : occurrences) {
		letters.push_back(occ.first);
	}
	int SOURCE = 0,
	    SINK = 1,
	    LEFT = 2,
	    RIGHT = LEFT + letters.size(),
	    CNT = RIGHT + n;
	flow_network G(CNT);
	for (int i = 0; i < n; i++) {
		if (found[i]) {
			continue;
		}
		G.add_edge(RIGHT + i, SINK, 1);
	}
	for (int i = 0; i < letters.size(); i++) {
		for (int j = 0; j < n; j++) {
			if (forbidden[j].find(letters[i]) != forbidden[j].end()) continue;
			G.add_edge(LEFT + i, RIGHT + j, 1);
		}
		G.add_edge(SOURCE, LEFT + i, occurrences[letters[i]]);
	}
	G.max_flow(SOURCE, SINK, false);
	for (int i = 0; i < letters.size(); i++) {
		for (int at = G.head[LEFT + i]; at != -1; at = G.e[at].nxt) {
			int v = G.e[at].v - RIGHT;
			if (0 <= v && v < n && G.e[at^1].cap == 1) {
				assert(!found[v] || found[v] == letters[i]);
				found[v] = letters[i];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (found[i]) {
			cout << found[i];
		} else {
			char c = 'a';
			while (fixed.find(c) != fixed.end() || forbidden[i].find(c) != forbidden[i].end()) {
				c++;
			}
			cout << c;
		}
	}
	cout << endl;
	return 0;
}
