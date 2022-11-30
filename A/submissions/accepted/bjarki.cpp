#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <cassert>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 2147483647;

struct node {
  int l, r;

  int end,
      slack,
      last_start;

  node() {}
  node(int _l, int _r) : l(_l), r(_r), end(0), slack(0), last_start(-1) { }
  node(int _l, int _r, ll _x) : node(_l,_r) {
      this->update(_x);
  }
  node(node a, node b) : node(a.l,b.r) {
      if (a.end > b.slack) {
          a.end -= b.slack;
          last_start = a.last_start;
          slack = a.slack;
          end = b.end + a.end;
      } else {
          b.slack -= a.end;
          last_start = b.last_start;
          end = b.end;
          slack = a.slack + b.slack;
      }
  }
  void update(ll v) {
      assert(l == r);
      if (v == 0) {
          end = 1;
          slack = 0;
          last_start = l;
      } else {
          end = 0;
          slack = 1;
          last_start = -1;
      }
  }
};

struct segment_tree {
  int n;
  vector<node> arr;
  segment_tree() { }
  segment_tree(const vector<ll> &a) : n(size(a)), arr(4*n) {
    mk(a,0,0,n-1); }
  node mk(const vector<ll> &a, int i, int l, int r) {
    int m = (l+r)/2;
    return arr[i] = l > r ? node(l,r) :
      l == r ? node(l,r,a[l]) :
      node(mk(a,2*i+1,l,m),mk(a,2*i+2,m+1,r)); }
  node update(int at, ll v, int i=0) {
    int hl = arr[i].l, hr = arr[i].r;
    if (at < hl || hr < at) return arr[i];
    if (hl == at && at == hr) {
      arr[i].update(v); return arr[i]; }
    return arr[i] =
      node(update(at,v,2*i+1),update(at,v,2*i+2)); }
  node query(int l, int r, int i=0) {
    int hl = arr[i].l, hr = arr[i].r;
    if (r < hl || hr < l) return node(hl,hr);
    if (l <= hl && hr <= r) return arr[i];
    return node(query(l,r,2*i+1),query(l,r,2*i+2)); }
};

int main() {
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    n += 1;

    map<int,vi> loc;
    rep(i,0,n) {
        int x;
        cin >> x;
        loc[x].push_back(i);
    }

    segment_tree st(vector<ll>(n, 1));
    vi cur(n, 1);

    int mx = 0,
        done = 0,
        last = -1,
        cnt = 0;
    iter(it,loc) {
        iter(jt,it->second) {
            cnt++;
            cur[*jt] = 0;
            st.update(*jt, 0);
            last = max(last, *jt);
        }

        while (done < n && cur[done] == 0) {
            done++;
        }

        auto res = st.query(done, last);

        int w = res.end;
        if (res.last_start >= 0 && res.last_start % 2 == 1) {
            w--;
        }

        mx = max(mx, w + last - (cnt - 1));
    }

    cout << mx << endl;

    return 0;
}

