#include <bits/stdc++.h>
#define f(i, s, k, l) for (int i = s; i < k; i += l)
#define for0(i, k) f(i, 0, k, 1)

#define pl pair<long long, long long>
#define pb push_back

#define vl vector<long long>
#define vi vector<int>
#define sz(x) (ll)(x).size()

using namespace std;
using ll = long long;
using ld = long double;

int main() {
    ll c, d;
    string x;
    cin >> c >> d;
    vl fizz, buzz, fizzbuzz;
    for(ll i = c; i <= d; i++) {
        cin >> x;
        if(x == "Fizz") fizz.pb(i);
        if(x == "Buzz") buzz.pb(i);
        if(x == "FizzBuzz") {
            fizz.pb(i);
            buzz.pb(i);
        }
    }

    ll f = d + 1;
    if(sz(fizz) > 1) f = fizz[1] - fizz[0];
    else if(sz(fizz) == 1) f = fizz[0];
    ll b = d + 1;
    if(sz(buzz) > 1) b = buzz[1] - buzz[0];
    else if(sz(buzz) == 1) b = buzz[0];


    cout << f << " " << b << endl;
}