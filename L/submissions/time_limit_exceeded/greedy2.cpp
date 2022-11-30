#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using bits = bitset<26>;

mt19937_64 rng(123456789);
ll m, n;
string res, resMaybe, needed;
vector<bits> ok;
vector<ll> required, okCount;

void sortPositions(vector<ll>& in) {
	sort(all(in), [](ll a, ll b){
		return okCount[a] > okCount[b];
	});
}

void solveGreedy() {
	vector<ll> done;
	string neededLater;
	//sortPositions(required);
	shuffle(all(required), rng);
	while (!required.empty()) {
		swap(needed.back(), needed[uniform_int_distribution<ll>(0, sz(needed) - 1)(rng)]);
		char c = needed.back();
		needed.pop_back();
		for (ll j = 0; j < sz(required); j++) {
			ll i = required[j];
			if (ok[i][c - 'a']) {
				done.push_back(i);
				swap(res[i], c);
				swap(required[j], required.back());
				required.pop_back();
				break;
			}
		}
		if (c != '*') {
			//sortPositions(done);
			shuffle(all(done), rng);
			bool swapped = false;
			for (ll i : done) {
				if (ok[i][c - 'a']) {
					swap(res[i], c);
					swapped = true;
					break;
				}
			}
			if (swapped) needed.push_back(c);
			else neededLater.push_back(c);
		}
	}
	for (ll i = 0; i < n; i++) {
		if (res[i] == '*') required.push_back(i);
	}
	//sortPositions(required);
	shuffle(all(required), rng);
	needed += neededLater;
	while (!needed.empty()) {
		swap(needed.back(), needed[uniform_int_distribution<ll>(0, sz(needed) - 1)(rng)]);
		char c = needed.back();
		needed.pop_back();
		for (ll j = 0; j < sz(required); j++) {
			ll i = required[j];
			if (ok[i][c - 'a']) {
				done.push_back(i);
				swap(res[i], c);
				swap(required[j], required.back());
				required.pop_back();
				break;
			}
		}
		if (c != '*') {
			//sortPositions(done);
			shuffle(all(done), rng);
			for (ll i : done) {
				if (ok[i][c - 'a']) {
					swap(res[i], c);
					break;
				}
			}
			needed.push_back(c);
		}
	}
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
	string maybe;
	for (ll i = 0; i < 26; i++) {
		needed += string(max(0ll, count[i]), (char)('a' + i));
		if (!isLim[i]) {
			maybe.push_back((char)('a' + i));
		}
	}
	resMaybe = res;
	okCount.assign(n, 0);
	for (ll i = 0; i < n; i++) {
		for (ll j = 0; j < 26; j++) {
			if (ok[i][j]) okCount[i]++;
		}
		if (resMaybe[i] != '*') continue;
		for (char c : maybe) {
			if (ok[i][c - 'a']) {
				resMaybe[i] = c;
				break;
			}
		}
		if (resMaybe[i] == '*') required.push_back(i);
	}
	solveGreedy();
	//cout << res << endl;
	for (ll i = 0; i < n; i++) {
		if (res[i] == '*') res[i] = resMaybe[i];
	}
	cout << res << endl;
}
