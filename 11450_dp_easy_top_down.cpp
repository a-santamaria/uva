#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<vector<int> > mat;
int M, C;
int memMat[201][20];

void printMat() {
    std::cout << "----------------" << '\n';
    for(int i = 0; i < mat.size(); i++) {
        for(int j = 0; j < mat[i].size(); j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << "----------------" << '\n';
}

int shop(int m, int curr) {
    if(curr == C) return 0;
    int mayor = -1;
    for(int i = 0 ; i < mat[curr].size(); i++) {
        if(m-mat[curr][i] >= 0) {
            int val = -1;
            if(memMat[m-mat[curr][i]][curr] == -1) {
                val = shop(m-mat[curr][i], curr + 1);
                memMat[m-mat[curr][i]][curr] = val;
            } else {
                val = memMat[m-mat[curr][i]][curr];
            }
            if (val != -1) {
                if(val + mat[curr][i] > mayor) mayor = val + mat[curr][i];
            }
        }
    }
    return mayor;
}

int main() {
    int cases;
    cin>>cases;
    while(cases--) {
        int K, aux;
        cin>>M>>C;
        mat.assign(C, vector<int>());
        memset(memMat, -1, sizeof(memMat));
        for (int i = 0; i < C; i++) {
            cin>>K;
            for(int j = 0; j < K; j++) {
                cin>>aux;
                mat[i].push_back(aux);
            }
        }
        // printMat();
        int sol = shop(M, 0);
        if(sol == -1) std::cout << "no solution" << '\n';
        else          std::cout << sol << '\n';
    }
    return 0;
}
