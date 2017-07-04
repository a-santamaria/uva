#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <cstring>

using namespace std;

int S;
int T;
const int MAX_NODES = 105;
const int INF = 1e9;
int n;

vector< vector<int> > g;
int f[MAX_NODES][MAX_NODES];
int parent[MAX_NODES];

int hasAugmenting() {
    memset(parent, -1, sizeof parent);
    int u, v;
    parent[S] = -2;
    int C[MAX_NODES];
    C[S] = INF;
    queue<int> q;
    q.push(S);
    while (!q.empty()) {
        u = q.front(); q.pop();
        for (int i = 0; i < g[u].size(); i++) {
            v = g[u][i];
            if (parent[v] == -1 && f[u][v] > 0) {
                
                q.push(v);
                parent[v] = u;
                C[v] = min(C[u], f[u][v]);
                if(v == T) return C[v];
            }
        }
    }
    return 0;
}

int ford_fulkerson() {
    int flow = 0;
    int u, v;
    while (true) {
        int c = hasAugmenting();
        if (!c) return flow;
        flow += c;
        v = T;
        while (v != S) {
            u = parent[v];
            f[u][v] -= c;
            f[v][u] += c;
            v = u;
        }
    }
}

int main() {
    int c;
    int cont = 1;
    while (cin >> n && n != 0) {
        g.assign(n+2, vector<int>());
        memset(f, 0, sizeof f);
        cin >> S >> T >> c;
        int x, y, cap;
        for (int i = 0; i < c; i++) {
            cin >> x >> y >> cap;
            g[x].push_back(y);
            g[y].push_back(x);
            f[x][y] += cap;
            f[y][x] += cap;
        }
        cout << "Network " << cont++ << '\n';
        cout << "The bandwidth is " << ford_fulkerson() << ".\n\n";
    }
    return 0;
}
