#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <map>

using namespace std;

const int S = 0;
const int T = 37;
const int PERSON_BEG = 1;
const int TSHIRT_BEG = 31;
const int MAX_NODES = 38;
const int INF = 1e9;
vector<vector<int> > g;
int f[MAX_NODES][MAX_NODES], parent[MAX_NODES];
map<string, int> tshirt;

int n, m;

void init_flow() {
    memset(f, 0, sizeof f);
    for(int i = PERSON_BEG; i < PERSON_BEG + m; i++) {
        f[S][i] = 1;
        g[S].push_back(i);
    }
    for(int i = TSHIRT_BEG; i < TSHIRT_BEG + 6; i++) {
        f[i][T] = n/6;
        g[i].push_back(T);
    }
}

int hasAugmenting() {
    int u, v;
    int C[MAX_NODES] = {INF};
    memset(parent, -1, sizeof parent);
    parent[S] = -2;
    queue<int> q;
    q.push(S);
    while(!q.empty()) {
        u = q.front();
        q.pop();
        for(int i = 0; i < g[u].size(); i++) {
            v = g[u][i];
            if(parent[v] == -1 && f[u][v] > 0) {
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
    while(true) {
        int c = hasAugmenting();
        if(!c) return flow;
        flow += c;
        int u = T;
        while(u != S) {
            int v = parent[u];
            f[v][u] -= c;
            f[u][v] += c;
            u = v;
        }
    }
}

int main() {

    tshirt.insert(make_pair("XS", 0));
    tshirt.insert(make_pair("S", 1));
    tshirt.insert(make_pair("M", 2));
    tshirt.insert(make_pair("L", 3));
    tshirt.insert(make_pair("XL", 4));
    tshirt.insert(make_pair("XXL", 5));

    int cases;
    cin >> cases;

    while(cases--) {
        cin >> n >> m;
        g.assign(MAX_NODES, vector<int>());
        init_flow();
        string s1;
        for(int i = 0; i < m; i++) {
            cin >> s1;
            g[ PERSON_BEG + i ].push_back( tshirt[s1] + TSHIRT_BEG );
            g[ tshirt[s1] + TSHIRT_BEG ].push_back( PERSON_BEG + i );
            f[ PERSON_BEG + i ][ tshirt[s1] + TSHIRT_BEG ] = 1;

            cin >> s1;
            g[ PERSON_BEG + i ].push_back( tshirt[s1] + TSHIRT_BEG );
            g[ tshirt[s1] + TSHIRT_BEG ].push_back( PERSON_BEG + i );
            f[ PERSON_BEG + i ][ tshirt[s1] + TSHIRT_BEG ] = 1;
        }

        int flow = ford_fulkerson();

        if(flow == m) cout << "YES\n";
        else          cout << "NO\n";

    }
    return 0;
}