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

vector<int> Divs(int a) {
    set<int> N;
    for(int i = 1; i*i <= a; i++) {
        if(a % i == 0) {
            N.insert(i);
            N.insert(a/i);
        }
    }

    vector<int> ALL;

    for(auto a : N) ALL.pb(a);
    return ALL;
}

int main() {
    cin.sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<string> A(m-n+1);
    for(int i = 0; i < m-n+1; i++) {
        cin >> A[i];
    }
    vector<int> D1;
    vector<int> D2;

    for(int i = n; i <= m; i++) {
        int index = i - n;
        if(A[index] == "Fizz" && D1.empty()) D1 = Divs(i); 
        if(A[index] == "Buzz" && D2.empty()) D2 = Divs(i);
        if(A[index] == "FizzBuzz") {
            if(D1.empty()) D1 = Divs(i);
            if(D2.empty()) D2 = Divs(i);
        }
    }

    D1.pb(1'000'001);
    D2.pb(1'000'001);
    int a = -1;
    int b = -1;

    for(int i = 0; i < D1.size(); i++) {
        bool good = true;
        for(int j = n; j <= m; j++) {
            int index = j - n;
            if(A[index] == "Fizz") {
                if(j % D1[i] != 0) good = false;
            } else if(A[index] == "FizzBuzz") {
                if(j % D1[i] != 0) good = false;
            } else {
                if(j % D1[i] == 0) good = false;
            }
        }
        if(good) a = D1[i];
    }
    for(int i = 0; i < D2.size(); i++) {
        bool good = true;
        for(int j = n; j <= m; j++) {
            int index = j - n;
            if(A[index] == "Buzz") {
                if(j % D2[i] != 0) good = false;
            } else if(A[index] == "FizzBuzz") {
                if(j % D2[i] != 0) good = false;
            } else {
                if(j % D2[i] == 0) good = false;
            }
        }
        if(good) b = D2[i];
    }
    cout << a << " " << b << endl;

}













