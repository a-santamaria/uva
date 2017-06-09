#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <set>

using namespace std;

vector<vector<int> > g;
bool color[105];
int n;
int currMax;
bool maxState[105];

bool hasBlackNeighbours(int ind) {
    for (int i = 0 ; i < g[ind].size(); i++) {
        if (color[ g[ind][i] ]) return true;
    }
    return false;
}

void printState() {
    bool first = true;
    for(int i = 0 ; i < n; i++) {
        if (maxState[i]) {
            if(first) {
                first = false;
            } else {
                cout<<" ";
            }
            cout << i+1;
        }
    }
    cout << '\n';
}

void bt(int ind, int cont) {
    if (ind == n) {
        if (cont > currMax) {
            currMax = cont;
            memcpy(maxState, color, sizeof(color));
        }
        return;
    }

    if (hasBlackNeighbours(ind)) {
         if (cont > currMax) {
            currMax = cont;
            memcpy(maxState, color, sizeof(color));
        }
    } else {
        color[ind] = 1;
        bt(ind+1, cont+1);
    }
    color[ind] = 0;
    bt(ind+1, cont);
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m;
    cin>>m;
    while (m--) {
        int a, b, v;
        cin>>n>>v;
        g.assign(n, vector<int>());
        for (int i = 0; i < v; i++) {
            cin >> a >> b;
            a--;
            b--;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        memset(color, 0, sizeof(color));
        
        currMax = 0;
        bt(0, 0);
        cout << currMax << '\n';
        printState();

    }
    return 0;
}
