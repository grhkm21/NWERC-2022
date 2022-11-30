#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll bits = 40;
constexpr ll mask = (1ll << bits) - 1;

ll query(string c) {
	cout << "? " << c << endl;
	ll res;
	cin >> res;
	return res;
}

void die(ll res) {
	cout << "! " << res << endl;
	exit(0);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll cur;
	cin >> cur;

	//for small n check separately: ~3bits queries
	for (ll i = 0; i < bits; i++) {
		if (cur != 0) cur = query("FlIp");
		cur = query("riGhT");
	}
	if (cur == 0) cur = query("fLiP");
	for (ll i = 0; i < bits; i++) {
		cur = query("LeFt");
		if (cur == 1) die(i+1);
	}

	//for large n do a random approch: ~n+2bits queries
	ll random = 0x3C1D'264A'3209'B812;
	ll state = 0;
	for (ll i = 0; i < bits; i++) {
		cur = query("rIghT");
		if (cur != (random & 1)) cur = query("FliP");
		random /= 2;
		state *= 2;
		state += cur;
		state &= mask;
	}
	ll expected = state;
	for (ll i = 0;; i++) {
		cur = query("RigHt");
		state *= 2;
		state += cur;
		state &= mask;
		if (state == expected) die(i+1);
	}
}
