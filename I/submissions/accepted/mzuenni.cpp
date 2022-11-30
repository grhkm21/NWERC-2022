#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll l, r;
	cin >> l >> r;
	vector<ll> a, b;
	for (ll i = l; i <= r; i++) {
		string s;
		cin >> s;
		if (s[0] == 'F') a.push_back(i);
		if (s[0] == 'B' || sz(s) == 8) b.push_back(i);
	}
	if (a.empty()) a.push_back(r+1);
	if (b.empty()) b.push_back(r+1);
	a.push_back(2*a.back());
	b.push_back(2*b.back());
	cout << a[1]-a[0] << " " << b[1]-b[0] << endl;
}
