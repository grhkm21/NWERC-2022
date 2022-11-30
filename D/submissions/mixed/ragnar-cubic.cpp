// This is cubic, but impossible to kill.
// @EXPECTED_RESULTS@: ACCEPTED, TIME_LIMIT_EXCEEDED
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

double a[1500][1500];
string b[710];

double s = acos(-1) / 2;

int main() {
	iostream::sync_with_stdio(false);
	cin.tie(nullptr);

	int h, w;
	cin >> h >> w;
	for(int r = 0; r < h; ++r) cin >> b[r];
	for(int r = 1; r <= 2 * h; r += 2) a[r][0] = r;
	for(int c = 1; c <= 2 * w; c += 2) a[0][c] = c;
	for(int r = 1; r <= 2 * h; ++r) {
		if(r % 2 == 1) {
			for(int c = 2; c <= 2 * w; c += 2) {
				double x = 1e9;
				if(b[(r - 1) / 2][(c - 1) / 2] == 'O') {
					x = a[r - 1][c - 1] + s;
				} else {
					x = a[r - 1][c - 1] + 2;
				}
				for(int r2 = 1; r2 < r; r2 += 2) {
					x = min(x, a[r2][c] + r - r2);
				}
				a[r][c] = x;
			}
		} else {
			for(int c = 1; c <= 2 * w; c += 2) {
				double x = 1e9;
				if(b[(r - 1) / 2][(c - 1) / 2] == 'O') {
					x = a[r - 1][c - 1] + s;
				} else {
					x = a[r - 1][c - 1] + 2;
				}
				for(int c2 = 1; c2 < c; c2 += 2) {
					x = min(x, a[r][c2] + c - c2);
				}
				a[r][c] = x;
			}
		}
	}
	cout << setprecision(10) << 5 * (min(a[2 * h][2 * w - 1], a[2 * h - 1][2 * w]) + 1) << endl;
}
