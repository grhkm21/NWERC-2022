#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

bool solve() {
	int n, k;
	cin >> n >> k;

	vector<pair<int,int>> pairs(n);
	for (auto &[a,b]: pairs) cin >> a >> b;
	sort(begin(pairs), end(pairs));

	do {
		vector<int> count(k+1);
		for (int i = 0; i < n; i++) {
			auto [a,b] = pairs[i];
			auto [c,d] = pairs[(i+1)%n];
			count[a] += c != a && d != a;
			count[b] += b != a && c != b && d != b;
			count[c] += a != c && b != c;
			count[d] += d != c && a != d && b != d;
		}
		if (*max_element(begin(count), end(count)) <= 2) {
			return true;
		}
	} while (next_permutation(begin(pairs), end(pairs)));

	return false;
}

int main() {
	cout << (solve() ? "possible" : "impossible") << '\n';
}
