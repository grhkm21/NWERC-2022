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
    ll n, k, a, b;
    cin >> n >> k;
    vector<set<ll>> adj(k);
    vector<bool> del(k, true);
    vector<bool> selfloop(k, false);
    for0(i, n) {
        cin >> a >> b;
        a--; b--;
        del[a] = del[b] = false;
        if(a == b) {
            selfloop[a] = true;
            continue;
        }
        adj[a].insert(b);
        adj[b].insert(a);
    }

    // count components
    vector<bool> vis(k, false);
    ll components = 0;
    for0(i, k) {
        if(del[i] || vis[i]) continue;
        components++;
        queue<ll> q;
        q.push(i);
        while(!q.empty()) {
            ll cur = q.front();
            q.pop();
            if(vis[cur]) continue;
            vis[cur] = true;
            for(ll v : adj[cur]) {
                if(!vis[v] && !del[i]) q.push(v);
            }
        }
    }

    // delete vertices with degree 1 that do not have any selfloops
    vl deg(k);
    for0(i, k) deg[i] = sz(adj[i]);
    vl newDeg = deg;
    for0(i, k) {
        if(deg[i] == 1 && newDeg[*(adj[i].begin())] > 1 && !selfloop[i]) {
            del[i] = true;
            newDeg[*(adj[i].begin())]--;
        }
    }

    // count vertices with deg 1 and deg 2
    vl count = {0, 0, 0};
    for0(i, k) {
        if(del[i]) continue;
        if(newDeg[i] > 2) {
            cout << "impossible" << endl;
            return 0;
        }
        count[newDeg[i]]++;
    }

    if(components == 1 && count[0] + count[1] == 0) cout << "possible" << endl;
    else if(count[0] + count[1] / 2 == components) cout << "possible" << endl;
    else cout << "impossible" << endl;

}