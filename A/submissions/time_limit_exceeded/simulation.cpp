#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 2147483647;

bool sorted(const vi &arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i-1] > arr[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    n += 1;
    vi arr(n);
    rep(i,0,n) {
        cin >> arr[i];
    }

    int cnt = 0;
    while (true) {
        if (sorted(arr)) break;
        cnt++;
        for (int i = 0; i+1 < n; i += 2) {
            if (arr[i] > arr[i+1]) {
                swap(arr[i], arr[i+1]);
            }
        }

        if (sorted(arr)) break;
        cnt++;
        for (int i = 1; i+1 < n; i += 2) {
            if (arr[i] > arr[i+1]) {
                swap(arr[i], arr[i+1]);
            }
        }
    }

    cout << cnt << endl;

    return 0;
}

