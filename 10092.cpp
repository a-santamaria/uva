#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

vector< vector<int> > g;
int f[1000+20+2][1000+20+2];
int parent[1000+20+2];
int s, t;

int hasAugmenting() {
    int u, v;
    memset(parent, -1, sizeof(parent));
    parent[s] = -2;
    vector<int> C(g.size(), 1e9);
    queue<int> q;
    q.push(s);
    while(!q.empty()) {
        u = q.front();
        q.pop();
        for(int i = 0; i < g[u].size(); i++) {
            v = g[u][i];
            if(parent[v] == -1 && f[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                C[v] = min(C[u], f[u][v]);
                if(v == t) return C[v];
            }
        }
    }
    return 0;
}

int edmondsKarp() {
    int flow = 0;
    while(true) {
        int c = hasAugmenting();
        if(c == 0) return flow;
        flow += c;
        int u = t, p;
        while(u != s) {
            p = parent[u];
            f[p][u] -= c;
            f[u][p] += c;
            u = p;
        }

    }
}

int main() {
    int numC, numP;
    while(cin >> numC >> numP && numC != 0 && numP != 0) {
        g.assign(numC+numP+3, vector<int>());
        memset(f, 0, sizeof f);
        int sumFlow = 0;
        s = 0;
        t = numC+numP+1;
        int num;
        for(int i = numP+1; i < numP+numC+1; i++) {
            g[i].push_back(t);
            cin >> num;
            sumFlow += num;
            f[i][t] = num;
        }
        int n, c;
        for(int i = 1; i <= numP; i++) {
            g[s].push_back(i);
            f[s][i] = 1;
            cin >> n;
            for(int j = 0; j < n; j++) {
                cin >> c;
                g[i].push_back( c + numP );
                f[i][ c + numP ] = 1;

                g[ c + numP ].push_back(i);
                f[ c + numP ][i] = 0;
            }
        }

        int flow = edmondsKarp();

        if(flow == sumFlow) {
            cout << "1\n";
            for(int u = numP+1; u < numP+numC+1; u++) {
               int cont = 0;
               for(int i = 0; i < g[u].size(); i++) {
                   int v = g[u][i];
                   if(!f[v][u]) {
                       if(cont++) cout << ' ';
                       cout << v;
                   }
               }
                cout << '\n';
            }
        } else {
            cout << "0\n";
        }
    }
    return 0;
}