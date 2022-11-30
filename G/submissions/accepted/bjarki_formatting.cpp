#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;
#define rep(i,a,b) for (auto i=(a); i<(b); ++i)
#define iter(it,c) for (auto it = (c).begin(); it != (c).end(); ++it)
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef long long ll;
const int INF = 2147483647;

int main() {
    string pattern;
    rep(i,0,25) {
        pattern += rand() % 2 == 0 ? '1' : '0';
    }

    int at = 0;
    string response;
    while (true) {
        char c;
        cin >> c;
        response += c;

        if (response.size() >= pattern.size() && equal(pattern.rbegin(), pattern.rend(), response.rbegin())) {
            cout << endl;
            cout << "   !  " << endl << "   " << response.size() - pattern.size() << "   " << endl;
            return 0;
        }

        if (at < (int)pattern.size() && pattern[at] != c) {
            cout << " " << endl;
            cout << "  ? flip " << endl;
            cout << endl;
            cin >> c;
        }

        cout << " ? right   " << endl;
        at++;
    }

    return 0;
}

