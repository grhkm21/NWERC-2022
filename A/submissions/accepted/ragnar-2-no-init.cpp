// This uses a range-update max-query segtree.
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

struct T {
	// Number of zeros and ones in the interval.
	int zeros, ones;
	// max over (ones left of cut) - (zeros right of cut) for cut in this interval.
	int inside;
	T(int x) : zeros{x == 0}, ones{x == 1}, inside{1} {} // NOLINT
	T(int zeros, int ones, int inside) : zeros(zeros), ones(ones), inside(inside) {}
};
T op(const T& l, const T& r) {
	return {l.zeros + r.zeros, l.ones + r.ones, max({l.inside + r.zeros, r.inside + l.ones})};
}
// All positions start at one and change to 0 one by one.
T _id{0, 0, 0};

struct SegmentTree {
	int n;
	vector<T> tree;
	T id;
	explicit SegmentTree(int _n) : n(_n), tree(2 * n, _id), id(_id) {}
	void update(int i, T val) {
		for(tree[i + n] = val, i = (i + n) / 2; i > 0; i /= 2)
			tree[i] = op(tree[2 * i], tree[2 * i + 1]);
	}
	T query(int l, int r) {
		T lhs = T(id), rhs = T(id);
		for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if(l & 1) lhs = op(lhs, tree[l++]);
			if(!(r & 1)) rhs = op(tree[r--], rhs);
		}
		return op(l == r ? op(lhs, tree[l]) : lhs, rhs);
	}
};

int main() {
	int n;
	cin >> n;
	n += 1;
	vector<int> v(n), ord(n);
	for(auto& x : v) cin >> x;
	iota(begin(ord), end(ord), 0);
	stable_sort(begin(ord), end(ord), [&](int i, int j) { return v[i] < v[j]; });
	SegmentTree st(n);
	for(int i = 0; i < n - 1; ++i) st.update(i, 1);
	int left_one   = 0;
	int right_zero = -1;
	int ans        = 0;
	for(int i = 0; i < n; ++i) {
		auto pos = ord[i];
		// position pos will change from 1 to 0.
		right_zero = max(right_zero, pos);
		while(left_one < n and v[left_one] <= v[pos]) ++left_one;
		st.update(pos, 0);
		auto m = st.query(left_one, right_zero).inside;
		if((m + i) % 2 != 1) --m;
		ans = max(ans, m);
	}
	cout << ans << endl;
}
