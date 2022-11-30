#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	double h, r, da, dw;
	cin >> h >> r >> da >> dw;

	double a = dw-da, b = h*h*da, c = h*da;
	double A = a*a, B = 2*a*c, C = -a*b;
	double x = (-B + sqrt(B*B - 4*A*C)) / (2*A);
	cout << fixed << setprecision(20) << x << '\n';
}
