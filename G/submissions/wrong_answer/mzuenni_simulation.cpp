#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

constexpr ll bits = 25;
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

vector<ll> toBitVector(ll x, ll b) {
	vector<ll> res;
	for (ll i = 0; i < b; i++, x /= 2) {
		res.push_back(x & 1);
	}
	reverse(all(res));
	return res;
}

void simulate(ll rand, ll origRead) {
	for (ll n = 3; n < bits; n++) {
		auto state = toBitVector(origRead >> (bits - n), n);
		ll read = 0;
		for (ll i = 0, random = rand; i < bits; i++) {
			ll cur = state[i % n];
			read *= 2;
			read += cur;
			read &= mask;
			if (cur != (random & 1)) cur ^= 1;
			state[i % n] = cur;
			random /= 2;
		}
		if (read == origRead) die(n);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll cur;
	cin >> cur;

	//for large n do a random approch: ~n+2bits queries
	ll rand = 0x1a27'e90e'c588'0dba;
	ll state = 0;
	ll read = 0;
	for (ll i = 0, random = rand; i < bits; i++) {
		cur = query("right");
		read *= 2;
		read += cur;
		read &= mask;
		if (cur != (random & 1)) cur = query("flip");
		random /= 2;
		state *= 2;
		state += cur;
		state &= mask;
	}
	//fix small n with simulation?
	simulate(rand, read);
	ll expected = state;
	for (ll i = 0;; i++) {
		cur = query("right");
		state *= 2;
		state += cur;
		state &= mask;
		if (state == expected) die(i+1);
	}
}
