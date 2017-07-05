#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
typedef long long ll;

#define MAX_N 205
#define INF 1e12
const int S = 0, T = 204;
int n, m;
vector< vector<int> > g;
ll f[MAX_N][MAX_N];
int parent[MAX_N];

inline int in(int id) { return id; }
inline int out(int id) { return 100 + id; }

ll hasAugmenting() {
    memset(parent, -1, sizeof parent);
    parent[S] = -2;
    ll C[MAX_N];
    C[S] = INF;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (parent[v] == -1 && f[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                C[v] = min(C[u], f[u][v]);
                if (v == T) return C[v];
            }
        }
    }
    return 0;
}

ll ford_fulkerson() {
    ll flow = 0;
    while (true) {
        ll c = hasAugmenting();
        if (!c) return flow;
        flow += c;
        int v = T;
        while (v != S) {
            int u = parent[v];
            f[u][v] -= c;
            f[v][u] += c;
            v = u;
        }
    }
}

int main() {
    ll c;
    int u, v;
    while (cin >> n) {
        memset(f, 0, sizeof f);
        g.assign(MAX_N, vector<int>());
        for (int i = 1; i < n+1; i++) {
            cin >> c;
            f[in(i)][out(i)] = c;
            g[in(i)].push_back(out(i));
            g[out(i)].push_back(in(i));
        }
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> u >> v >> c;
            g[out(u)].push_back(in(v));
            g[in(v)].push_back(out(u));
            f[out(u)][in(v)] += c;
        }
        int b, d;
        cin >> b >> d;    
        for (int i = 0; i < b; i++) {
            cin >> u;
            g[S].push_back(in(u));
            f[S][in(u)] = INF;
        }

        for (int i = 0; i < d; i++) {
            cin >> u;
            g[out(u)].push_back(T);
            f[out(u)][T] = INF;
        }

        cout << ford_fulkerson() << '\n';
    }    
    return 0;
}