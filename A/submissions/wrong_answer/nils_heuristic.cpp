#include <bits/stdc++.h>
using namespace std;
 
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;

int n;
const int MAXN = 400007;
const int INF = 1000000007;
vi A, A_SORTED;

int EVEN[2*MAXN] = {0};
int ODD[2*MAXN] = {0};
int evens = 0;
int odds = 0;

int guess(int turn){
    vi A2;
    int n2;
    int lo = -1;
    int hi = -1;
    rep(c1,0,n){
        if(A[c1] != A_SORTED[c1]){
            lo = c1;
            break;
        }
    }
    for(int c1 = n-1; c1 >= 0; c1--){
        if(A[c1] != A_SORTED[c1]){
            hi = c1;
            break;
        }
    }
    if(lo == -1)return 0;
    rep(c1,lo,hi+1){
        A2.push_back(A[c1]);
    }
    n2 = sz(A2);

    int mi = INF;
    int pos = 0;
    rep(c1,0,n2){
        if(A2[c1] < mi){
            mi = A2[c1];
            pos = c1;
        }
    }

    int ans = pos;
    if(lo%2 == turn%2){
        ans = pos + ((pos+1)%2);
    }
    else{
        ans = pos + (pos%2);
    }
    if(pos == 0)ans = 0;

    int ma = -INF;
    pos = 0;
    rep(c1,0,n2){
        if(A2[c1] >= ma){
            ma = A2[c1];
            pos = c1;
        }
    }
    int ans2;
    if(hi%2 != turn%2){
        int j = n2-1-pos;
        ans2 = j + ((j+1)%2);
    }
    else{
        int j = n2-1-pos;
        ans2 = j + (j%2);
    }
    if(pos == hi)ans2 = 0;
    return max(ans, ans2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
 
    ll a,b,c,d;
 
    cin >> n;
    n++;
    rep(c1,0,n){
        cin >> a;
        A.push_back(a);
        A_SORTED.push_back(a);
    }
    sort(all(A_SORTED));

    rep(c1,0,n-1){
        if(A[c1] > A[c1+1]){
            if(c1%2 == 0){
                EVEN[evens] = c1;
                evens++;
            }
            else{
                ODD[odds] = c1;
                odds++;
            }
        }
    }

    int lim = 100000000;
    int swaps = 0;
    int turn = 0;
    while(1){
        if(evens+odds == 0 || swaps > lim)break;
        if(turn%2 == 0){
            for(int c1 = 0; c1 < evens; c1++){
                int i = EVEN[c1];
                if(A[i] > A[i+1]){
                    swap(A[i], A[i+1]);
                    if(i-1 >= 0 && A[i-1] > A[i]){
                        ODD[odds] = i-1;
                        odds++;
                    }
                    if(i+2 < n && A[i+1] > A[i+2]){
                        ODD[odds] = i+1;
                        odds++;
                    }
                }
            }
            swaps += evens;
            evens = 0;
        }
        else{
            for(int c1 = 0; c1 < odds; c1++){
                int i = ODD[c1];
                if(A[i] > A[i+1]){
                    swap(A[i], A[i+1]);
                    if(i-1 >= 0 && A[i-1] > A[i]){
                        EVEN[evens] = i-1;
                        evens++;
                    }
                    if(i+2 < n && A[i+1] > A[i+2]){
                        EVEN[evens] = i+1;
                        evens++;
                    }
                }
            }
            swaps += odds;
            odds = 0;
        }
        turn++;
    }

    cout << turn+guess(turn) << "\n";
 
    return 0;
}