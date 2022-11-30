#include <bits/stdc++.h>
using namespace std;

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

	// prioritize indices with fewer allowed letters
	vector<int> p(n);
	iota(begin(p), end(p), 0);
	sort(begin(p), end(p), [&](int i, int j) {
		return __builtin_popcount(mask[i]) < __builtin_popcount(mask[j]);
	});

	vector<int> count(26);
	string res(n,'?');
	auto backtrack = [&](const auto &self, int j) -> void {
		if (j == n) {
			for (int k = 0; k < 26; k++) {
				if (count[k] < min_count[k]) return;
			}
			cout << res << '\n';
			exit(0);
		}
		int i = p[j];

		// prioritize letters that have not yet met their quota
		vector<int> v(26);
		iota(begin(v), end(v), 0);
		sort(begin(v), end(v), [&](int k, int l) {
			return min_count[k]-count[k] > min_count[l]-count[l];
		});

		for (int k: v) if (mask[i] & (1 << k)) {
			if (count[k] == max_count[k]) continue;
			count[k]++;
			res[i] = 'a'+k;
			self(self, j+1);
			res[i] = '?';
			count[k]--;
		}
	};
	backtrack(backtrack, 0);
	cout << "impossible" << '\n';
}
