// will probably need more than 5000 queries for large n...
// but only roughly 10*n for any n... (worst cases are n = 2^x)
#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

ll query(const string& s) {
	cout << "? " << s << endl;
	ll res;
	cin >> res;
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll x;
	cin >> x;
	if (x == 0) x = query("flip");

	for (ll l = 1; x == 1; l *= 2) {
		for (ll i = 0; i < l; i++) {
			x = query("right");
			if (x == 1) x = query("flip");
		}
		for (ll i = 0; i < l; i++) x = query("left");
	}
	x = query("flip");
	x = query("right");
	ll res = 1;
	while (x == 0) {
		res++;
		x = query("right");
	}
	cout << "! " << res << endl;
}
