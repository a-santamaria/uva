#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;

// 26 letters x 9 users = 234 programs
// 0 - 9 = 10 computers
int match[300];
bool marcas[300];
vector < vector<int> > g;
char mapa[300];

bool hasAugmentingPath(int v) {
  if(marcas[v]) return false;
  marcas[v] = true;

  for(int u : g[v]) {
    if(match[u] == -1 || hasAugmentingPath(match[u])) {
      match[u] = v;
      match[v] = u;
      return true;
    }
  }
  return false;
}

int main() {
  while(!cin.eof()) {
    string line;
    int index = 10;
    g.assign(300, vector<int>());
    while(getline(cin, line) && line != "") {
      stringstream iss(line);
      string s1, s2;
      iss >> s1 >> s2;
      int num = s1[1] - '0';
      char leter = s1[0];
      for(int i = 0; i < s2.size()-1; i++) {
        int comp = s2[i] - '0';
        for(int j = 0; j < num; j++) {
          mapa[index + j] = leter;
          g[index + j].push_back(comp);
          g[comp].push_back(index + j);
        }
      }
      index += num;
    }
    
    memset(match, -1, sizeof(match));
    for(int i = 10; i < index; i++) {
      if(match[i] == -1) {
        memset(marcas, false, sizeof(marcas));
        hasAugmentingPath(i);
      }
    }

    int cont = 0;
    for(int i = 0; i < 10; i++) {
      if (match[i] != -1) cont++;
    }
    if(cont < index - 10) {
      cout << '!';
    }
    else {
      for(int i = 0; i < 10; i++) {
        cout << (match[i] == -1 ? '_' : mapa[ match[i] ]) ;
      }
    }
    cout << '\n';
  }
}