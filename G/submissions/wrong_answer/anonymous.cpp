#include <bits/stdc++.h>
using namespace std;

constexpr int NMAX = 1000;


int main() {

  vector<int> val(NMAX, 0);
  cin >> val[0];

  for (int i = 1; i < NMAX; ++i)
    cout << "? right" << endl, cin >> val[i];

  cout << "? flip" << endl;
  cin >> val[NMAX-1];

  for (int i = NMAX - 2, newval; i >= 0; --i) {
    cout << "? left" << endl;
    cin >> newval;
    if (newval != val[i]) { // i == NMAX-1 mod n
      cout << "! " << NMAX - 1 - i << endl;
      exit(0);
    }
  }

  cout << "! " << NMAX << endl;
}
