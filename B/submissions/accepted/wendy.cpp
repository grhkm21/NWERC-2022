#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

ll h, rad, d1, d2;

ld eval(ld h1) {
    ld x1 = h * h * d1 + h1 * h1 * (d2 - d1);
    ld x2 = 2.0 * (h * d1 + h1 * (d2 - d1));
    return x1 / x2;
}

int main() {
    cin >> h >> rad >> d1 >> d2;

    ld l = 0.0;
    ld r = (ld) h;
    for0(i, 200) {
        ld m1 = (2 * l + r)/ 3.0;
        ld m2 = (2 * r + l) / 3.0;
        if(eval(m1) < eval(m2)) r = m2;
        else l = m1;
    }

    cout << fixed << setprecision(10) << r << endl;
}