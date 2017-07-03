#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <cstring>

using namespace std;

const int S = 0;
const int T =  731;
const int LETTER_BEG = 1;
const int NOMBRES_BEG = 27;
const int PROBLEMS_BEG = 703;
const int MAX_NODES = 750; //730 = 26 + 26*26 + 26 + 2
const int INF = 1e9;
int n, k;

vector< vector<int> > g;
int f[MAX_NODES][MAX_NODES];
int parent[MAX_NODES];
map<string, int> nombres;
map<int, string> nombresR;

void init_flow() {
    memset(f, 0, sizeof f);
    for (int i = LETTER_BEG; i < LETTER_BEG + n; i++) {
        g[S].push_back(i);
        f[S][i] = 1;
    }
    for (int i = PROBLEMS_BEG; i < PROBLEMS_BEG + n; i++) {
        g[i].push_back(T);
        f[i][T] = 1;
    }
}
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
    int cases;
    string s;
    cin >> cases;
    int cont = 1;
    while (cases--) {
        cin >> n;
        g.assign(MAX_NODES, vector<int>());
        nombres.clear();
        nombresR.clear();
        map<string, int>::iterator it;
        init_flow();
        int index = NOMBRES_BEG;
        for (int i = 0; i < n; i++) {
            cin >> k;
            
            for (int j = 0; j < k; j++) {
                cin >> s;
                transform(s.begin(), s.end(), s.begin(), ::tolower);

                it = nombres.find(s);
                if (it == nombres.end()) {
                    g[ LETTER_BEG + (s[0] - 'a') ].push_back(index);
                    g[index].push_back( LETTER_BEG + (s[0] - 'a') );
                    f[ LETTER_BEG + (s[0] - 'a') ][index] = 1;

                    g[index].push_back( PROBLEMS_BEG + i );
                    g[PROBLEMS_BEG + i].push_back( index );
                    f[index][ PROBLEMS_BEG + i ] = 1;

                    nombresR[index] = s;
                    nombres[s] = index++;
                } else {
                    g[ LETTER_BEG + (s[0] - 'a') ].push_back( it->second );
                    g[ it->second ].push_back( LETTER_BEG + (s[0] - 'a') );
                    f[ LETTER_BEG + (s[0] - 'a') ][it->second] = 1;

                    g[ it->second ].push_back( PROBLEMS_BEG + i );
                    g[PROBLEMS_BEG + i].push_back(  it->second  );
                    f[ it->second ][ PROBLEMS_BEG + i ] = 1;
                }
            }
        }

        cout << "Case #" << cont++ << ":\n";
        int flow = ford_fulkerson();
        // cerr << "flow " << flow << endl;
        vector<string> res;
        for (int v = PROBLEMS_BEG; v < PROBLEMS_BEG + n; v++) {
            for(int j = 0; j < g[v].size(); j++) {
                int u = g[v][j];
                if (u != T && f[v][u] == 1) {
                    res.push_back( (char)toupper(nombresR[u][0]) + nombresR[u].substr(1));
                }
            }
        }
        sort(res.begin(), res.end());

        for(string s :  res) {
            cout << s << '\n';
        }
    }
    return 0;
}