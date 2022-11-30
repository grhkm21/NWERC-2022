#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

int main() {
	i64 a, b;
	char foo;
	cin >> a >> foo >> b;

	for (i64 k = 1; k <= 1e6; k++) {
		i64 n = k*b, r = k*a;
		if (r < n-1 || r > n*(n-1)/2) continue;

		cout << n << ' ' << n-1 << '\n';

		vector<int> dist(n, 1);
		dist[0] = 0;
		r -= n-1;
		
		vector<int> v(n);
		for (i64 i = 1; i < n; i++) {
			i64 t = min(i-1,r);
			dist[i] += t;
			r -= t;
			v[dist[i]] = i;
			cout << v[dist[i]-1]+1 << ' ' << i+1 << '\n';
		}
		assert(r == 0);

		return 0;
	}
	
	cout << "impossible" << '\n';
}
