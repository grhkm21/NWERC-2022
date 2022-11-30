#include <algorithm>
#include <iostream>
#include <vector>

struct tup {
  int val, i;
  bool operator<(const tup &other) const {
    return val != other.val ? val < other.val : i < other.i;
  }
};

int solve(const std::vector<int>& a, int offset = 0) {
  int n = static_cast<int>(a.size());
  std::vector<tup> v(n);
  for (int i = 0; i < n; ++i) v[i].val = a[i];

  int reps = 0;
  for (; !std::is_sorted(v.begin(),v .end()) && reps < 100; ++reps)
    for (int j = (reps+offset)%2; j+1 < n; j += 2)
      if (v[j].val > v[j+1].val)
        std::swap(v[j], v[j+1]);

  for (int i = 0; i < n; ++i)
    v[i].i = i;
  std::sort(v.begin(), v.end());

  int maxdiff = 0;
  for (int i = 0; i < n; ++i)
    maxdiff = std::max(maxdiff, std::abs(i - v[i].i));
  return reps + maxdiff;
}

std::vector<int> invert(const std::vector<int>& a) {
  std::vector<tup> v(a.size());
  for (size_t i = 0; i < a.size(); ++i)
    v[i].val = a[i], v[i].i = static_cast<size_t>(i);
  std::sort(v.begin(), v.end());
  std::vector<int> res(a.size());
  for (size_t i = 0; i < res.size(); ++i)
    res[i] = v[i].i;
  return res;
}

int main() {
  int n;
  std::cin >> n;
  n += 1;
  std::vector<int> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i];

  int forward = solve(a);
  int backward0 = solve(invert(a), 0);
  int backward1 = solve(invert(a), 1);

  if (backward0 % 2 == 0) ++backward0;
  if (backward1 % 2 == 1) ++backward1;
  std::cout << std::min(forward, std::min(backward0, backward1)) << std::endl;
}
