#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(auto i = (a); i < (b); i++)
#define pb push_back
#define fs first
#define sc second
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

const double EPS = 1e-9;
const double pi = acos(-1);

// c = pi * r * r, area of a circle
// height p
// a,w
// x = p/2   y = (h+p)/2 
// d1 = pi * r * r * p * w
// d2 = pi * r * r * (h - p) + a
// (p/2 * pi * r * r * w * p + (h+p)/2 * pi * r * r * (h-p) * a)
// /(w * p + (h - p) * a)
// a * (h - p) * c
//
double r,h,a,w;
double c(double p) {
    double t1 = p/2 * pi * r * r * w * p + (h+p)/2 * pi * r * r * (h-p)*a;
    double t2 = (w * p + (h - p) * a);
    return t1/t2;

}

int main() {
    cin.sync_with_stdio(false);
    cin >> h >> r >> a >> w;
    double lo = 0, hi = h;
    rep(i,0,100) {
        double mid1 = lo + (hi - lo)/3;
        double mid2 = hi - (hi - lo)/3;
        if(c(mid1) < c(mid2)) {
            hi = mid2;
        } else {
            lo = mid1;
        }
    }
    cout << setprecision(10) << lo << endl;

}

