#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <sstream>
#include <map>
#include <cstdio>

using namespace std;

#define maxV 1010

int f[maxV][maxV];
vector< vector <int> > g;
int parent[maxV];
int s, t;

int hasAugmenting() { //bfs
    queue<int> q;
    memset(parent, -1, sizeof(parent));
    parent[s] = -2;
    q.push(s);
    int C[g.size()] = {1e9};

    int u, v;
    bool encontre = false;
    while(!q.empty()) {
        u = q.front(); q.pop();
        //cerr << " curr  " << u << endl;
        for(int i = 0; i < g[u].size(); i++) {
            v = g[u][i];
            if(parent[v] == -1 && f[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                C[v] = min(C[u], f[u][v]);
                if (v == t) return C[v];
            }
        }
    }
    return 0;
}

int edmonsKarp() {
    int flow = 0;
    while(true) {
        int c = hasAugmenting();
        cerr << "augmenting " << c << endl;
        if(c == 0) return flow;
        flow += c;
        cerr << "curr flow " << c << endl;
        int v = t;
        while(v != s) {
            int p = parent[v];
            f[p][v] -= c;
            f[v][p] += c;

            v = p;
        }
    }
    cerr << "voy a retornar " << flow << endl;
    return flow;
}

int main() {
    s = 0;
    map<string, int>::iterator it;
    int cases;
    cin >> cases;
    string line;
    getchar();
    getchar();
    while(cases--) {
        g.assign(1, vector<int>());
        
        int index = 1;
        map<string, int> party;
        map<string, int> person;
        map<string, int> club;
        vector<string> reverseMap;
        memset(f, 0, sizeof(f));
        string s;
        int indP, indPar, indC;
        cerr << "antes" << endl;
        while(getline(cin, line) && line != "") {
            stringstream ss;
            ss << line;
            ss >> s;
            it = person.find(s);
            if(it != person.end()) {
                indP = it->second;
            } else {
                reverseMap.push_back(s);
                indP = person[s] = index++;
                g.push_back(vector<int>());
            }

            ss >> s;
            it = party.find(s);
            if(it != party.end()) {
                indPar = it->second;
            } else {
                reverseMap.push_back(s);
                indPar = party[s] = index++;
                g.push_back(vector<int>());
            }
            

            while(ss >> s) {
                it = club.find(s);
                if(it != club.end()) {
                    indC = it->second;
                } else {
                    reverseMap.push_back(s);
                    indC = club[s] = index++;
                    g.push_back(vector<int>());
                }
            }

            
            g[indPar].push_back(indP);
            g[indP].push_back(indPar);

            g[indP].push_back(indC);
            g[indC].push_back(indP);

            f[indPar][indP] = 1;
            f[indP][indPar] = 0;

            f[indP][indC] = 1;
            f[indC][indP] = 0;

            cerr << "index " << index << endl;
        }
        t = index;
        cerr << "t: " << t << endl;
        for(it = club.begin(); it != club.end(); it++) {
            g[it->second].push_back(t);
            f[it->second][t] = 1;
            f[t][it->second] = 0;
        }

        for(it = party.begin(); it != party.end(); it++) {
            g[0].push_back(it->second);
            f[0][it->second] = club.size()-1 / 2;
            f[it->second][0] = 0;
        }

        for(int i = 0; i < g.size(); i++) {
            cerr << i << ": ";
            for(int j = 0; j < g.size(); j++) {
                cerr << f[i][j] << " - ";
            }
            cerr << endl;
        }

        cout << "flow " << edmonsKarp() << '\n';

        for(it = person.begin(); it != person.end(); it++) {
            for(int i = 0; i < g[it->second].size(); i++) {
                int v = g[it->second][i];
                if(f[it->second][v] == 0) {
                    cout << it->first << " " << reverseMap[v-1] << endl;
                    break;
                }
            }
        }
    }
    
    return 0;
}
