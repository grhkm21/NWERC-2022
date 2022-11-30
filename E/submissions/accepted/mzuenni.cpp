#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

void die() {
	cout << "impossible" << endl;
	exit(0);
}
int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll a, b;
	char c;
	cin >> a >> c >> b;
	ll n = b;
	while (2*a > (n-1)*b) n += b;
	a *= n / b;
	ll cur = n*(n-1) / 2;
	vector<ll> pref(n);
	for (ll i = 1; i < n; i++) pref[i] = i - 1;
	for (ll i = n - 1; i > 0 && a < cur; i--) {
		ll tmp = min(pref[i],cur - a);
		pref[i] -= tmp;
		cur -= tmp;
	}
	if (a != cur) {
		cout << "impossible" << endl;
	} else {
		cout << n << " " << n-1 << endl;
		for (ll i = 1; i < n; i++) {
			cout << i+1 << " " << pref[i]+1 << endl;
		}
	}
}
