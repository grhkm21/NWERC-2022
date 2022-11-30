#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

#define pb push_back
#define mp make_pair
#define eb emplace_back
#define all(a) begin(a), end(a)
#define has(a, b) (a.find(b) != a.end())
#define fora(i, n) for(int i = 0; i < n; i++)
#define forb(i, n) for(int i = 1; i <= n; i++)
#define forc(a, b) for(const auto &a : b)
#define ford(i, n) for(int i = n; i >= 0; i--)
#define maxval(t) numeric_limits<t>::max()
#define minval(t) numeric_limits<t>::min()
#define imin(a, b) a = min(a, b)
#define imax(a, b) a = max(a, b)
#define sz(x) (int)(x).size()
#define pvec(v) copy(all(v), ostream_iterator<decltype(v)::value_type>(cout, " "))

#define dbgs(x) #x << " = " << x
#define dbgs2(x, y) dbgs(x) << ", " << dbgs(y)
#define dbgs3(x, y, z) dbgs2(x, y) << ", " << dbgs(z)
#define dbgs4(w, x, y, z) dbgs3(w, x, y) << ", " << dbgs(z)

using ll = long long;
using ld = long double;

bool test(ll a, ll b) {
	vector<ll> c(b);
	c[0] = 1;
	c[1] = b - 1;
	a -= b - 1;
	for (int i = 2; i < b; i++) {
		c[i] = min(max(c[i - 1] - 1, 0ll), a);
		c[i - 1] -= c[i];
		a -= c[i];
	}
	if (a != 0) {
		return false;
	}
	cout << b << ' ' << (b - 1) << '\n';
	int last = 1;
	int next = 2;
	for (int i = 1; i < b; i++) {
		fora(j, c[i]) {
			cout << next << ' ' << last << '\n';
			next++;
		}
		last = next - 1;
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	ll a, b;
	char c;
	cin >> a >> c >> b;

	ll g = __gcd(a, b);
	a /= g; b /= g;

	if (a < b - 1) {
		cout << "impossible" << endl;
		return 0;
	}
	if (a < b) {
		test(a, b);
		return 0;
	}
	ll aa = a, bb = b;
	while (bb + b <= 1000000) {
		aa += a;
		bb += b;
	}
	test(aa, bb);
}
