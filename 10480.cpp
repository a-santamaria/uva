#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <set>

using namespace std;
#define max_n 502
#define INF 1e12 // poner mas grande
typedef long long ll;
vector< vector<int> > g;
int parent[max_n];
ll f[max_n][max_n];
const int S = 1;
const int T = 2;
int n, m;

int hasAugmenting() {
  memset(parent, -1, sizeof parent);
  parent[S] = -2;
  ll C[max_n];
  C[S] = INF;
  queue<int> q;
  q.push(S);
  int u, v;
  while (!q.empty()) {
    u = q.front(); q.pop();
    for (int i = 0; i < g[u].size(); i++) {
      v = g[u][i];
      if(parent[v] == -1 && f[u][v] > 0) {
        q.push(v);
        parent[v] = u;
        C[v] = min(C[u], f[u][v]);
        if(v == T) return C[v];
      }
    }
  }

}

ll fordFulkerson() {
  int u, v;
  ll flow = 0;
  while (true) {
    ll c = hasAugmenting();
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

void solve() {
  queue<int> q;
  q.push(S);
  bool marcas[n+1];
  memset(marcas, false, sizeof marcas);
  marcas[S] = true;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for(int i = 0; i < g[u].size(); i++) {
      int v = g[u][i];
      if(marcas[v]) continue;
      if (f[u][v] > 0) {
        marcas[v] = true;
        q.push(v);
      }
    }
  }

  set< pair<int, int > > sol;
  set< pair<int, int > >::iterator it;
  for (int i = 1; i < n+1; i++) {
    if(marcas[i]) {
      for(int j = 0; j < g[i].size(); j++) {
        int u = g[i][j];
        if(!marcas[u])
          sol.insert(make_pair(i, u));
      }
    }
  }

  for (it = sol.begin(); it != sol.end(); it++) {
    cout << it->first << " " << it->second << "\n";
  }

}

int main() {
  while (cin >> n >> m && n != 0 && m != 0) {
    g.assign(n+2, vector<int>());
    int x, y, c;
    memset(f, 0, sizeof f);
    for (int i = 0; i < m; i++) {
      cin >> x >> y >> c;
      g[x].push_back(y);
      g[y].push_back(x);
      f[x][y] = c;
      f[y][x] = c;
    }
    ll flow = fordFulkerson();

    solve();
    cout << '\n';
  }
  return 0;
}
