#include <stdio.h>
#include <math.h>
#define rep(E, F) for (E = 0; E < (F); E++)
#define per(E, F) for (E = (F) - 1; E >= 0; E--)
int min(int a, int b) { if (a > b) return b; return a; }
int max(int a, int b) { if (a < b) return b; return a; }
int get_int()
{
	int r = 0, c = getchar(), s = 1;
	while (c != '-' && c < '0' || c > '9') c = getchar();
	while (c == '-') s *= -1, c = getchar();
	while (c >= '0' && c <= '9') r = r*10 + c - '0', c = getchar();
	return s*r;
}

double vol(double h, double t) { return t*t*M_PI*h; }
double foo(double x, double h, double t, double m1, double m2)
{
	double h1 = x/2.0, h2 = x + (h - x)/2.0, v1 = vol(x, t)*m1, v2 = vol(h - x, t)*m2;
	return (v1*h1 + v2*h2)/(v1 + v2);
}

int main()
{
	double h = get_int(), t = get_int(), da = get_int(), dw = get_int(), r = 0.0, s = h;
	while (s - r > 1e-9)
	{
		double m1 = (r + r + s)/3.0, m2 = (r + s + s)/3.0;
		if (foo(m1, h, t, dw, da) < foo(m2, h, t, dw, da)) s = m2;
		else r = m1;
	}
	printf("%f\n", r);
	return 0;
}
