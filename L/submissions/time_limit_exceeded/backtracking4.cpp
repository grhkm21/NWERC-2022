#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using bits = bitset<26>;

mt19937_64 rng(987654321);
ll m, n;
string res;
vector<bits> ok;
string needed, maybe;

bool solveMaybe() {
	string tmp = res;
	for (ll i = 0; i < n; i++) {
		if (tmp[i] != '*') continue;
		for (char c : maybe) {
			if (ok[i][c - 'a']) {
				tmp[i] = c;
				break;
			}
		}
		if (tmp[i] == '*') return false;
	}
	res = tmp;
	return true;
}

bool solveNeeded(ll i = 0) {
	if (i >= sz(needed)) return solveMaybe();
	for (ll j = 0; j < n; j++) {
		if (res[j] == '*' && ok[j][needed[i] - 'a']) {
			res[j] = needed[i];
			if (solveNeeded(i + 1))	return true;
			res[j] = '*';
		}
	}
	return false;
}


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> m >> n;
	res = string(n, '*');
	ok.assign(n, -1);
	vector<ll> count(26, 0);
	bits isLim;
	for (ll i = 1; i < m; i++) {
		string a, b;
		cin >> a >> b;
		bits isCurLim;
		vector<ll> curCount(26, 0);
		for (ll j = 0; j < n; j++) {
			if (b[j] == 'G') {
				res[j] = a[j];
				curCount[a[j] - 'a']++;
			} else if (b[j] == 'Y') {
				ok[j][a[j] - 'a'] = false;
				curCount[a[j] - 'a']++;
			} else {
				ok[j][a[j] - 'a'] = false;
				isCurLim[a[j] - 'a'] = true;
			}
		}
		for (ll j = 0; j < 26; j++) {
			if (isCurLim[j]) {
				isLim[j] = true;
				count[j] = curCount[j];
			} else {
				count[j] = max(count[j], curCount[j]);
			}
		}
	}
	for (char c : res) {
		if (c != '*') count[c - 'a']--;
	}
	for (ll i = 0; i < n; i++) {
		string cur;
		for (ll j = 0; j < 26; j++) {
			if (count[j] > i) cur += (char)('a' + j);
		}
		shuffle(all(cur), rng);
		needed += cur;
	}
	for (ll i = 0; i < 26; i++) {
		if (!isLim[i]) {
			maybe.push_back((char)('a' + i));
		}
	}
	shuffle(all(maybe), rng);
	//cout << needed << endl;
	//cout << maybe << endl;
	solveNeeded();
	cout << res << endl;
}
