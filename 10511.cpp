#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <sstream>
#include <map>
#include <cstdio>

using namespace std;

// int f[10000][10000];
map< pair<int,int>, int > f;
vector< vector <int> > g;
int parent[10000];
int s, t;

int hasAugmenting() { //bfs
    queue<int> q;
    memset(parent, -1, sizeof(parent));
    parent[s] = -2;
    q.push(s);
    vector<int> C(g.size());
    C[s] = 1e9;
    int u, v;
    bool encontre = false;
    while(!q.empty()) {
        u = q.front(); q.pop();
        //cerr << " curr  " << u << endl;
        for(int i = 0; i < g[u].size(); i++) {
            v = g[u][i];
            if(parent[v] == -1 && f[make_pair(u,v)] > 0) {
                q.push(v);
                parent[v] = u;
                C[v] = min(C[u], f[make_pair(u,v)]);
                if (v == t) return C[v];
            }
        }
    }
    return 0;
}
vector<string> reverseMap;

int edmonsKarp() {
    int flow = 0;
    while(true) {
        int c = hasAugmenting();
        if(c == 0) return flow;
        flow += c;
        int v = t;
        while(v != s) {
            int p = parent[v];
            f[make_pair(p, v)] -= c;
            f[make_pair(v, p)] += c;

            v = p;
        }
    }
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
        g.assign(10002, vector<int>());
        f.clear();
        int index = 1;
        map<string, int> party;
        map<string, int> person;
        map<string, int> club;
        reverseMap.clear();
        reverseMap.push_back("source");
        string s;
        int indP, indPar, indC;
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
            }

            ss >> s;
            it = party.find(s);
            if(it != party.end()) {
                indPar = it->second;
            } else {
                reverseMap.push_back(s);
                indPar = party[s] = index++;
            }
            
            g[indPar].push_back(indP);
            g[indP].push_back(indPar);
            f[make_pair(indPar, indP)] = 1;
            f[make_pair(indP, indPar)] = 0;

            while(ss >> s) {
                it = club.find(s);
                if(it != club.end()) {
                    indC = it->second;
                } else {
                    reverseMap.push_back(s);
                    indC = club[s] = index++;
                }

                g[indP].push_back(indC);
                g[indC].push_back(indP);
                f[make_pair(indP, indC)] = 1;
                f[make_pair(indC, indP)] = 0;
            }

        }
        t = index;
        for(it = club.begin(); it != club.end(); it++) {
            g[it->second].push_back(t);
            f[make_pair(it->second, t)] = 1;
        }

        for(it = party.begin(); it != party.end(); it++) {
            g[0].push_back(it->second);
            f[make_pair(0, it->second)] = (club.size()-1) / 2;
        }
        reverseMap.push_back("target");

        int flow = edmonsKarp();
        if (flow < club.size()) cout << "Impossible.\n";
        else {
            for(it = club.begin(); it != club.end(); it++) {
                for(int i = 0; i < g[it->second].size(); i++) {
                    int v = g[it->second][i];
                    if(v == t) continue;
                    if(f[make_pair(it->second, v)] == 1) {
                        cout << reverseMap[v] << " " << it->first << "\n";
                        break;
                    }
                }
            }
        }
        
        if (cases) cout << '\n';
    }
    
    return 0;
}
