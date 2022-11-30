#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int main() {
	int l, r;
	cin >> l >> r;
	int a = 0, b = 0;
	for (int at = l; at <= r; at++) {
		string s;
		cin >> s;
		if (s == "Fizz" || s == "FizzBuzz") {
			a = gcd(a, at);
		}
		if (s == "Buzz" || s == "FizzBuzz") {
			b = gcd(b, at);
		}
	}
	if (a == 0) {
		a = r+1;
	}
	if (b == 0) {
		b = r+1;
	}
	cout << a << " " << b << endl;
	return 0;
}
