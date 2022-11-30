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

bool allVisBfs(vl start, vector<bool> &vis, vector<set<ll>> &adj) {
    queue<ll> q;
    for(ll v : start) q.push(v);
    while(!q.empty()) {
        ll cur = q.front();
        q.pop();
        if(vis[cur]) continue;
        vis[cur] = true;
        for(ll v : adj[cur]) {
            if(!vis[v]) q.push(v);
        }
    }
    bool allVis = true;
    for(bool x : vis) allVis &= x;
    return allVis;
}

int main() {
    ll n, k, a, b;
    cin >> n >> k;
    vector<set<ll>> adj(k);
    vl deg(k);
    for0(i, n) {
        cin >> a >> b;
        a--; b--;
        adj[a].insert(b);
        adj[b].insert(a);
    }

    for0(i, k) deg[i] = sz(adj[i]);

    // check if connected
    vector<bool> visAll(k, false);
    bool connected = allVisBfs({0}, visAll, adj);

    vector<bool> vis(k, false);
    vl degNew = deg;

    // remove vertices with degree 1
    ll del = 0;
    for0(i, k) {
        if(deg[i] == 1) {
            vis[i] = true;
            degNew[*(adj[i].begin())]--;
            del++;
        }
    }
    // possible if graph is empty
    if(del == k) {
        cout << "possible" << endl;
        return 0;
    }

    vl pathEnds;
    for0(i, k) {
        if(degNew[i] > 2) {
            cout << "impossible" << endl;
            return 0;
        } else if(!vis[i] && degNew[i] <= 1) pathEnds.pb(i);
    }

    // check if the remaining graph is a cycle and if the original graph is connected
    if(sz(pathEnds) == 0) {
        if(connected) cout << "possible" << endl;
        else cout << "impossible" << endl;
        return 0;
    }

    // check if the remaining graph is a collection of paths
    bool paths = allVisBfs(pathEnds, vis, adj);
    if(paths) cout << "possible" << endl;
    else cout << "impossible" << endl;
}