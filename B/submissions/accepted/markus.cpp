#include <iostream>
#include <iomanip>
#include <cmath>
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

ld pi = 2 * acos(0);

ld h, r, d1, d2;

ld get(ld h1) {
	ld h2 = h - h1;
	ld w1 = d1 * pi * r * h1;
	ld w2 = d2 * pi * r * h2;
	ld p1 = h1 / 2;
	ld p2 = h1 + h2 / 2;
	ld ans = (w1 * p1 + w2 * p2) / (w1 + w2);
	return ans;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> h >> r >> d2 >> d1;

	ld lo = 0;
	ld hi = h;

	fora(_, 100) {
		ld t1 = (2 * lo + hi) / 3;
		ld t2 = (lo + 2 * hi) / 3;
		if (get(t1) > get(t2)) {
			lo = t1;
		} else {
			hi = t2;
		}
	}
	cout << setprecision(20) << lo << endl;
}
