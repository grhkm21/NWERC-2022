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
	explicit T(int x) : zeros{x == 0}, ones{x == 1}, inside{1} {}
	T(int zeros, int ones, int inside) : zeros(zeros), ones(ones), inside(inside) {}
};
T op(const T& l, const T& r) {
	// Either cut in the left interval and add all zeros on the right interval, or cut in the right
	// interval and add all ones in the left interval.
	return {l.zeros + r.zeros, l.ones + r.ones, max({l.inside + r.zeros, r.inside + l.ones})};
}
// 'Empty' interval.
T _id{0, 0, 0};

struct SegmentTree {
	int n;
	vector<T> tree;
	T id;
	explicit SegmentTree(int _n, T init) : n(_n), tree(2 * n, init), id(_id) {
		for(int i = n - 1; i >= 0; --i) tree[i] = op(tree[2 * i], tree[2 * i + 1]);
	}
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
	// All positions start at one and change to 0 one by one.
	SegmentTree st(n, T(1));
	int left_one   = 0;
	int right_zero = -1;
	int ans        = 0;
	for(int i = 0; i < n; ++i) {
		auto pos = ord[i];
		// position pos will change from 1 to 0.
		right_zero = max(right_zero, pos);
		while(left_one < n and v[left_one] <= v[pos]) ++left_one;
		st.update(pos, T(0));
		auto m = st.query(left_one, right_zero).inside;
		if((m + i) % 2 != 1) --m;
		ans = max(ans, m);
	}
	cout << ans << endl;
}
