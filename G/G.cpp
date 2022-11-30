#include <bits/stdc++.h>
using namespace std;

// helper functions
int right() {
  cout << "? right" << endl << flush;
  int r;
  cin >> r;
  return r;
}

int left() {
  cout << "? left" << endl << flush;
  int r;
  cin >> r;
  return r;
}

int flip() {
  cout << "? flip" << endl << flush;
  int r;
  cin >> r;
  return r;
}

void submit(int r) { cout << "! " << r << endl << flush; }

int cur, steps, pattern[50];
deque<int> prev50;

int main() {
  // random pattern
  for (int i = 0; i < 50; i++) {
    pattern[i] = rand() & 1;
  }

  cin >> cur;

  // first, solve for n <= 50
  // clear right 50, go back, flip, go at most 50, see if sees the light
  for (int i = 0; i < 55; i++) {
    if (cur) {
      cur = flip();
    }
    cur = right();
  }

  for (int i = 0; i < 55; i++) {
    cur = left();
  }

  cur = flip();

  for (int i = 1; i <= 50; i++) {
    cur = right();
    if (cur) {
      submit(i);
      return 0;
    }
  }

  // now, we set the next 50 to pattern
  for (int i = 0; i < 50; i++) {
    if (cur != pattern[i]) {
      cur = flip();
    }
    cur = right();
  }

  // and keep walking until we find pattern
  // we add the current bit, then pop front until it matches
  while (prev50.size() < 50) {
    steps++;
    prev50.push_back(cur);
    while (!prev50.empty()) {
      // check if prev50 matches pattern already
      bool match = true;
      for (int i = 0; i < prev50.size(); i++) {
        if (pattern[i] != prev50[i]) {
          match = false;
          break;
        }
      }
      if (match) {
        break;
      }

      // if not, we pop front
      prev50.pop_front();
    }
    cur = right();
  }

  submit(steps);
}
