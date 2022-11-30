#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;
using lld = __float128;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll h, r, d1, d2;
	cin >> h >> r >> d1 >> d2;

	auto f = [&](lld x){
		lld c2 = x / 2;
		lld c1 = x + (h - x) / 2;
		return (c1 * d1 * (h - x) + c2 * d2 * x) / ((h - x) * d1 + x * d2);
	};

	lld l = 0;
	lld u = h;
	for (ll i = 0; i < 500; i++) {
		lld llu = (l + l + u) / 3;
		lld luu = (l + u + u) / 3;
		if (f(llu) < f(luu)) {
			u = luu;
		} else {
			l = llu;
		}
	}
	cout << fixed << setprecision(10) << (ld)l << endl;
}
