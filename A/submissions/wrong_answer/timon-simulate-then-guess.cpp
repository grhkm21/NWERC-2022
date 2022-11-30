#include <algorithm>
#include <iostream>
#include <vector>

struct tup {
  int val, i;
  bool operator<(const tup &other) const {
    return val != other.val ? val < other.val : i < other.i;
  }
};

int main() {
  int n;
  std::cin >> n;
  n += 1;
  std::vector<tup> a(n);
  for (int i = 0; i < n; ++i)
    std::cin >> a[i].val;

  int reps = 0;
  for (; !std::is_sorted(a.begin(), a.end()) && reps < 100; ++reps)
    for (int j = reps%2; j+1 < n; j += 2)
      if (a[j].val > a[j+1].val)
        std::swap(a[j], a[j+1]);

  for (int i = 0; i < n; ++i)
    a[i].i = i;
  std::sort(a.begin(), a.end());

  int maxdiff = 0;
  for (int i = 0; i < n; ++i) {
    maxdiff = std::max(maxdiff, std::abs(i - a[i].i));
  }
  std::cout << (reps + maxdiff) << std::endl;
}
