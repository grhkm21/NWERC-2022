#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()

using ll = long long;
using ld = double;

ld sq(ld x) {
	return x*x;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll h, r, d1, d2;
	cin >> h >> r >> d1 >> d2;

	auto f = [&](ld x){
		return (4.0l*d1*sq(h/2.0l-x)
		     + 8.0l*d1*x*(h/2.0l-x) 
		     + sq(x)*d2
		     + 3.0l*d1*sq(x))
		     / (2.0l * (2.0l*(h/2.0l-x)*d1
		     + x*(d1+d2)));
	};

	ld l = 0;
	ld u = h;
	for (ll i = 0; i < 500; i++) {
		ld llu = (l + l + u) / 3;
		ld luu = (l + u + u) / 3;
		if (f(llu) < f(luu)) {
			u = luu;
		} else {
			l = llu;
		}
	}
	cout << fixed << setprecision(10) << l << endl;
}
