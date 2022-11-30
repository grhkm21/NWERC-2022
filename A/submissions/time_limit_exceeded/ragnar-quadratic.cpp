#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

int main() {
	int n;
	cin >> n;
	n += 1;
	vector<int> v(n), ord(n);
	for(auto& x : v) cin >> x;
	iota(begin(ord), end(ord), 0);
	stable_sort(begin(ord), end(ord), [&](int i, int j) { return v[i] < v[j]; });
	int left_one = 0, right_zero = -1, ans = 0;
	for(int i = 0; i < n; ++i) {
		auto pos = ord[i];
		// position pos will change from 1 to 0.
		right_zero = max(right_zero, pos);
		while(left_one < n and v[left_one] <= v[pos]) ++left_one;
		// cut just after x. Count 1 at pos <= x, and 0 as pos > x
		for(int x = left_one, s = i - left_one + 1; x < right_zero; ++x)
			ans = max(ans, (s += v[x] <= v[pos] ? -1 : 1) - (x + 1) % 2);
	}
	cout << ans << endl;
}
