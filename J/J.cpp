#include <bits/stdc++.h>
// #include <bitset>
using namespace std;

struct Interval {
  int l, r, idx;
};

bool cmp(Interval a, Interval b) {
  if (a.l != b.l) {
    return a.l < b.l;
  }
  return a.r > b.r;
}

const int N = 2e5;
const int INF = 1e9;

int n, right_index[N + 1], ans[N + 1];
vector<Interval> intervals;

int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  cin >> n;
  intervals.resize(n);

  for (int i = 0; i < n; i++) {
    cin >> intervals[i].l >> intervals[i].r;
    intervals[i].idx = i;
    intervals[i].r += intervals[i].l;
  }

  sort(intervals.begin(), intervals.end(), cmp);

  for (int i = 0; i < n; i++) {
    int r = intervals[i].r;
    if (right_index[0] < r) {
      ans[intervals[i].idx] = 0;
      right_index[0] = r;
    } else {
      int largest = -1, L = 0, R = n;
      while (R >= L) {
        int M = (L + R) / 2;
        if (right_index[M] >= r) {
          largest = M;
          L = M + 1;
        } else {
          R = M - 1;
        }
      }
      ans[intervals[i].idx] = largest + 1;
      right_index[largest + 1] = max(right_index[largest + 1], intervals[i].r);
    }
  }

  for (int i = 0; i < n; i++) {
    cout << ans[i] << " ";
  }
  cout << endl;
}
