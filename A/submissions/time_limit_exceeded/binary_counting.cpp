#include <bits/stdc++.h>
using namespace std;
//template <class T> int size(const T &x) { return x.size(); }
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 2147483647;

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    n += 1;

    vi arr(n);
    rep(i,0,n) {
        cin >> arr[i];
    }

    vi tmp = arr;
    sort(tmp.begin(), tmp.end());

    int mx = 0;
    rep(i,0,n) {
        vi cur(n);
        rep(j,0,n) {
            cur[j] = arr[j] < tmp[i] ? 0 : 1;
        }

        int wait_last = 0,
            last_idx = -1,
            cnt = 0;
        bool ones_in_front = false;
        rep(j,0,n) {
            if (cur[j] == 0) {
                cnt++;
                if (ones_in_front) {
                    if (last_idx == -1) {
                        wait_last = j % 2 == 0 ? 1 : 0;
                    } else {
                        int w = (j - last_idx - 1);
                        wait_last = max(wait_last + 1 - w, j % 2 == 0 ? 1 : 0);
                    }
                    last_idx = j;
                }
            } else {
                ones_in_front = true;
            }
        }
        mx = max(mx, wait_last + last_idx - (cnt - 1));
    }

    cout << mx << endl;

    return 0;
}

