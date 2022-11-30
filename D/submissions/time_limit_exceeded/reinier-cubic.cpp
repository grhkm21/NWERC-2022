#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define all(v) (v).begin(), (v).end()

const ld PI = acos((ld)-1);
ld w, h;
ld r;
vector<vector<bool>> S;

ld point_to_circ(ld dx, ld dy) {
	ld a = sqrt(dx * dx + dy * dy);
	return sqrt(a * a - r * r) + (PI / 4 + atan2(dx, dy) - acos(r / a)) * r;
}

ld square_to_square(ll d) {
	return sqrt((2 * r + 2 * d) * (2 * r + 2 * d) + (2 - 2 * r) * (2 - 2 * r));
}

ld square_to_circ(ll d) {
	return point_to_circ(2 * d + r, 2 - r);
}

ld circ_to_circ(ll d) {
	return 2 * point_to_circ(d, 1);
}

ld start_to_circ(ll d) {
	return point_to_circ(2 * d + 1, 1);
}

ld start_to_square(ll d) {
	return sqrt((2 * d + 1 + r) * (2 * d + 1 + r) + (1 - r) * (1 - r));
}

ld dist(ll d, bool s1, bool s2) {
	if(s1 && s2) {
		return square_to_square(d);
	} else if(!s1 && !s2) {
		return circ_to_circ(d);
	} else {
		return square_to_circ(d);
	}
}

ld start_dist(ll d, bool s) {
	if(s) {
		return start_to_square(d);
	} else {
		return start_to_circ(d);
	}
}

void run() {
	cin >> h >> w;
	// cin >> r;
	r = 1;

	S = vector<vector<bool>>(w, vector<bool>(h));
	for(ll i = 0; i < h; i++) {
		string row;
		cin >> row;
		for(ll j = 0; j < w; j++) {
			S[j][i] = row[j] == 'X';
		}
	}

	vector<vector<ld>> NE(w, vector<ld>(h, 2 * w + 2 * h)), SW(w, vector<ld>(h, 2 * w + 2 * h));
	for(ll i = 0; i < w; i++) {
		NE[i][0] = start_dist(i, S[i][0]);
	}
	for(ll i = 0; i < h; i++) {
		SW[0][i] = start_dist(i, S[0][i]);
	}
	ld res = 2 * w + 2 * h;
	for(ll i = 0; i < w; i++) {
		for(ll j = 0; j < h; j++) {
			if(i < w - 1) {
				for(ll j2 = j; j2 < h; j2++) {
					SW[i + 1][j2] =
					    min(SW[i + 1][j2], NE[i][j] + dist(j2 - j, S[i][j], S[i + 1][j2]));
				}
			} else {
				res = min(res, NE[i][j] + start_dist(h - 1 - j, S[i][j]));
			}
			if(j < h - 1) {
				for(ll i2 = i; i2 < w; i2++) {
					NE[i2][j + 1] =
					    min(NE[i2][j + 1], SW[i][j] + dist(i2 - i, S[i][j], S[i2][j + 1]));
				}
			} else {
				res = min(res, SW[i][j] + start_dist(w - 1 - i, S[i][j]));
			}
		}
	}

	cout << 10*res / 2 << endl;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout << fixed << setprecision(20);
	run();
	return 0;
}
