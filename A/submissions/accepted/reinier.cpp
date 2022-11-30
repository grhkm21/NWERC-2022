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
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define REP(i,n) rep(i,0,n)
#define all(v) (v).begin(), (v).end()
#define rs resize
#define DBG(x) cerr << __LINE__ << ": " << #x << " = " << (x) << endl


typedef ii S;
const int n = 1<<20;
S t[2*n];

S combine(S l, S r) {
    return {l.x+r.x,max(l.y+r.x, r.y-l.x)};
}

void update(int i, S v) {
    for (t[i+=n] = v; i /= 2; )
        t[i] = combine(t[2*i], t[2*i+1]);
}

S query(int l, int r) {
    S resL = {0, 0}, resR = {0,0};
    for (l += n, r += n; l < r; l/=2, r/=2) {
        if (l&1) resL = combine(resL, t[l++]);
        if (r&1) resR = combine(t[--r], resR);
    }
    return combine(resL, resR);
}

void run() {
    ll n;
    cin >> n;
    n += 1;
    vi A(n);
    vii B(n);
    for (ll i = 0; i < n; i++) {
        cin >> A[i];
        B[i] = {A[i], i};
    }
    sort(all(B));
    ll res = 0;
    ll j = 0;
    for (ll i = 0; i < n; i++) {
        update(B[i].y, {1, B[i].y%2==0 ? B[i].y+1 : B[i].y});
        if (i+1 < n && B[i].x == B[i+1].x) continue;
        while (j < n && A[j] <= B[i].x) j++;
        res = max(res, query(j, n).y-j);
    }
    cout << res << endl;
}

signed main() {
    // DON'T MIX "scanf" and "cin"!
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(20);
    run();
    return 0;
}
