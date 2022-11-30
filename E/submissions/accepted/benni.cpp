#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(auto i = (a); i < (b); i++)
#define pb push_back
#define fs first
#define sc second
typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

const double EPS = 1e-9;

ll compare(ii a, ii b) {
    ll Y = a.fs * b.sc - a.sc * b.fs;
    if(Y == 0) {
        return 0;
    }
    if(Y < 0) return -1;
    if(Y > 0) return 1;
    assert(false);
}

void prll_sol(vi A) {
    ll n = 0;
    for(ll i = 0; i < A.size(); i++) n += A[i];
    cout << n << " " << n-1 << endl;
    ll vert = 0;
    for(ll i = 0; i < A[1]; i++) {
        cout << 1 << " " << 1+i+1 << endl;
        vert = 1+i+1;
    }
    ll at = vert+1;
    for(ll i = 2; i < A.size(); i++) {
        for(ll j = 0; j < A[i]; j++) {
            cout << vert << " " << at << endl;
            at++;
        }
        vert = at-1;
    }
}

int main() {
    cin.sync_with_stdio(false);

    ll a,b;
    char c;
    cin >> a >> c >> b;
    vector<ll> D = {1};
    ii F = ii(0,1);
    ii O = ii(a,b);
    ll cnt = 0;
    while(true) {
        if(compare(F,O) == 0) {
            prll_sol(D);
            return 0;
        }
        ll mx = -1;
        for(ll i = 1; i <= D.size(); i++) {
            ii NE_F = ii(F.fs + i, F.sc + 1);
            if(compare(NE_F,O) != 1) {
                mx = i;
            }
        }
        if(mx == -1) {
            cout << "impossible" << endl;
            return 0;
        }

        F = ii(F.fs + mx, F.sc + 1);
        if(mx == D.size()) D.push_back(1);
        else D[mx] += 1;
    }
}









