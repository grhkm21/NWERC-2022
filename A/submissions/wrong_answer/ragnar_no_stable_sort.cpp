// This uses a range-update max-query segtree.
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

using T = int;
using U = int;
using I = int; // exclusive right bounds
T t_id;
U u_id;
T op(T a, T b) { return max(a, b); }     // query for maximum
void join(U& a, U b) { a += b; }         // updates are adding numbers
void apply(T& t, U u, int x) { t += u; } // the maximum changes by the added update
T convert(const I& i) { return i; }
struct LazySegmentTree {
	struct Node {
		int l, r, lc, rc;
		T t;
		U u;
		Node(int l, int r, T t = t_id) : l(l), r(r), lc(-1), rc(-1), t(t), u(u_id) {}
	};
	int N;
	vector<Node> tree;
	vector<I>& init;
	LazySegmentTree(vector<I>& init) : N(init.size()), init(init) { // NOLINT
		tree.reserve(2 * N - 1);
		tree.emplace_back(0, N);
		build(0, 0, N);
	}
	void build(int i, int l, int r) {
		auto& n = tree[i];
		if(r > l + 1) {
			int m = (l + r) / 2;
			n.lc  = tree.size();
			n.rc  = n.lc + 1;
			tree.emplace_back(l, m);
			tree.emplace_back(m, r);
			build(n.lc, l, m);
			build(n.rc, m, r);
			n.t = op(tree[n.lc].t, tree[n.rc].t);
		} else
			n.t = convert(init[l]);
	}
	void push(Node& n, U u) {
		apply(n.t, u, n.r - n.l);
		join(n.u, u);
	}
	void push(Node& n) {
		push(tree[n.lc], n.u);
		push(tree[n.rc], n.u);
		n.u = u_id;
	}
	T query(int l, int r, int i = 0) {
		auto& n = tree[i];
		if(r <= n.l || n.r <= l) return t_id;
		if(l <= n.l && n.r <= r) return n.t;
		return push(n), op(query(l, r, n.lc), query(l, r, n.rc));
	}
	void update(int l, int r, U u, int i = 0) {
		auto& n = tree[i];
		if(r <= n.l || n.r <= l) return;
		if(l <= n.l && n.r <= r) return push(n, u);
		push(n);
		update(l, r, u, n.lc);
		update(l, r, u, n.rc);
		n.t = op(tree[n.lc].t, tree[n.rc].t);
	}
};

int main() {
	int n;
	cin >> n;
	n += 1;
	vector<int> v(n), ord(n);
	for(auto& x : v) cin >> x;
	iota(begin(ord), end(ord), 0);
	sort(begin(ord), end(ord), [&](int i, int j) { return v[i] < v[j]; });
	vector<int> init(n - 1);
	for(int i = 0; i < n - 1; ++i) init[i] = i + 1;
	LazySegmentTree st(init);
	int left_one   = 0;
	int right_zero = -1;
	int ans        = 0;
	for(int i = 0; i < n; ++i) {
		auto pos = ord[i];
		// position pos will change from 1 to 0.
		right_zero = max(right_zero, pos);
		if(pos == left_one) {
			++left_one;
			while(left_one < n and v[left_one] <= v[pos]) ++left_one;
		}
		st.update(0, pos, +1);
		st.update(pos, n - 1, -1);
		if(left_one < right_zero) {
			auto m = st.query(left_one, right_zero);
			if((m + i) % 2 != 1) --m;
			ans = max(ans, m);
		}
	}
	cout << ans << endl;
}
