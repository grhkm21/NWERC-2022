#include <bits/stdc++.h>
using namespace std;

long long mn(long long n) {
	return n-1;
}
long long mx(long long n) {
	return n*(n-1)/2;
}

int main() {
	long long a, b;
	cin >> a;
	cin.get();
	cin >> b;

	long long k = 1;
	while (mx(b * k) < k * a) {
		if (mn(b * k) > k * a) {
			break;
		}
		k++;
	}
	a = a*k;
	b = b*k;
	if (mn(b) > a || mx(b) < a) {
		cout << "impossible" << endl;
		return 0;
	}
	cout << b << " " << b-1 << endl;
	vector<int> path;
	vector<pair<int, int> > res;
	path.push_back(1);
	for (int at = 2; at <= b; at++) {
		long long left = b - at;
		long long take = min(a - left, (long long)path.size());
		if (take == (long long)path.size()) {
			path.push_back(at);
		}
		cout << path[take-1] << " " << at << endl;
		a -= take;
	}

	return 0;
}
