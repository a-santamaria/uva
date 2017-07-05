#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <climits>

using namespace std;

#define MAX_N 150
#define INF INT_MAX
int n, m;
int s = 1;
int t;
int f[MAX_N][MAX_N];
int parent[MAX_N];
vector< vector<int> > g;

int hasAugmenting() {
    int u, v;
    memset(parent, -1, sizeof parent);
    parent[s] = -2;
    int C[MAX_N];
    C[s] = INF;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        u = q.front(); q.pop();
        for (int i = 0; i < g[u].size(); i++) {
            v = g[u][i];
            if (parent[v] == -1 && f[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                C[v] = min(C[u], f[u][v]);
                if (v == t) return C[v];
            }
        }
    }
    return 0;
}
int ford_fulkerson() {
    int flow = 0; 
    while (true) {
        int c = hasAugmenting();
        if (!c) return flow;
        flow += c;
        int v = t;
        while (v != s) {
            int u = parent[v];
            f[u][v] -= c;
            f[v][u] += c;
            v = u;
        }
    }
}

int in(int id) {
    if (id == 1) return id;
    if (id == n) return (id << 1);
    return (id << 1); 
}

int out(int id) {
    if (id == 1) return id;
    if (id == n) return (id << 1);
    return (id << 1) - 1;
}

int main() {
    while (cin >> n >> m && n != 0 && m != 0) {
        g.assign( MAX_N, vector<int>());
        t = (n << 1);
        memset(f, 0, sizeof f);
        int id, id2, c;
        for (int i = 0; i < n-2; i++) {
            cin >> id >> c;
            g[in(id)].push_back(out(id));
            g[out(id)].push_back(in(id));
            f[in(id)][out(id)] += c;
        }

        for (int i = 0; i < m; i++) {
            cin >> id >> id2 >> c;

            g[out(id)].push_back(in(id2));
            g[in(id2)].push_back(out(id));
            f[out(id)][in(id2)] += c;

            g[out(id2)].push_back(in(id));
            g[in(id)].push_back(out(id2));
            f[out(id2)][in(id)] += c;
        }

        int flow = ford_fulkerson();
        cout << flow << '\n';
    }
    return 0;
}