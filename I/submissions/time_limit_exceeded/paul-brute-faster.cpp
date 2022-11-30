#include <iostream>
#include <vector>
using namespace std;

bool fizz[100001], buzz[100001];

int main() {
	int c, d;
	cin >> c >> d;
	for (int k = c; k <= d; k++) {
		string s; cin >> s;
		fizz[k] = s[0] == 'F';
		buzz[k] = !isdigit(s[0]) && s[ssize(s)-4] == 'B';
	}

	for (int a = 1; a <= 1e6; a++) {
		bool ok = true;
		for (int k = c; k <= d; k++) {
			if (fizz[k] != (k%a == 0)) ok = false;
			if (!ok) break;
		}
		if (ok) {
			cout << a << ' ';
			break;
		}
	}

	for (int b = 1; b <= 1e6; b++) {
		bool ok = true;
		for (int k = c; k <= d; k++) {
			if (buzz[k] != (k%b == 0)) ok = false;
			if (!ok) break;
		}
		if (ok) {
			cout << b << '\n';
			break;
		}
	}
}
