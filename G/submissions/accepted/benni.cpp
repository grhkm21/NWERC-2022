#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(auto i = (a); i < (b); i++)
#define pb push_back
#define fs first
#define sc second
typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;

const double EPS = 1e-9;

int main() {
    cin.sync_with_stdio(false);
    srand(time(NULL));
    vector<int> Pattern;
    for(int i = 0; i < 20; i++) {
        Pattern.pb(rand() % 2);
    }

    vector<int> Have;

    int s;
    int at = 0;
    int corr = 0;
    while(true) {
        cin >> s;
        Have.pb(s);
        if(s != Pattern[at % 20]) {
            cout << "? flip" << endl;
            cin >> s;
        }


        bool same = true;
        if(Have.size() < 20) same = false;
        else {
            for(int i = 0; i < 20; i++) {
                if(Pattern[19 - i] != Have[(int)Have.size() - i - 1]) same = false;
            } 
        }

        if(same) {
            cout << "! " << Have.size() - Pattern.size() << endl;
            return 0;
        }

        // check if done
        //
        at++;

        cout << "? left" << endl;
    }
}

