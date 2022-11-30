#include <bits/stdc++.h>
using namespace std;

long double pi = acos(-1.0L);

long double h, r, da, dw;
long double com(long double w) {
	long double total = w * dw + (h-w) * da;
	return (dw * (w*w/2) + da * ((h-w)*(h-w)/2 + (h-w)*w)) / total;
}

int main() {
	cin >> h >> r >> da >> dw;

	long double lo = 0,
	            hi = h;
	for (int it = 0; it < 10000; it++) {
		long double w1 = lo + (hi-lo)/3,
			    w2 = lo + 2*(hi-lo)/3;
		if (com(w1) < com(w2)) {
			hi = w2;
		} else {
			lo = w1;
		}
	}

	cout << setprecision(12) << lo << endl;

	return 0;
}
