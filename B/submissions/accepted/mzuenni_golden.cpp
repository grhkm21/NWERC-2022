#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = long double;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll h, r, d1, d2;
	cin >> h >> r >> d1 >> d2;

	auto f = [&](ld x){
		ld c2 = x / 2;
		ld c1 = x + (h - x) / 2;
		return (c1 * d1 * (h - x) + c2 * d2 * x) / ((h - x) * d1 + x * d2);
	};

	ld l = 0;
	ld u = h;
	ld inv = (sqrt(5.0l) - 1) / 2;
	ld x1 = u - inv * (u - l);
	ld x2 = l + inv * (u - l);
	ld f1 = f(x1);
	ld f2 = f(x2);
	for (ll i = 0; i < 500; i++) {
		if (f1 < f2) {
			u = x2;
			x2 = x1;
			f2 = f1;
			x1 = u - inv * (u - l);			
			f1 = f(x1);
		} else {
			l = x1;
			x1 = x2;
			f1 = f2;
			x2 = l + inv * (u - l);
			f2 = f(x2);
		}
	}

	cout << fixed << setprecision(10) << l << endl;
}
