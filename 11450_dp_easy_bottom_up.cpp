#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<vector<int> > mat;
int M, C;
bool memMat[20][201];

void printMat() {
    std::cout << "----------------" << '\n';
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 17; j++) {
            std::cout << memMat[i][j] << " ";
        }
        std::cout << '\n';
    }
    std::cout << "----------------" << '\n';
}


int main() {
    int cases;
    cin>>cases;
    while(cases--) {
        int K, aux;
        cin>>M>>C;
        mat.assign(C, vector<int>());
        memset(memMat, false, sizeof(memMat));
        for (int i = 0; i < C; i++) {
            cin>>K;
            for(int j = 0; j < K; j++) {
                cin>>aux;
                mat[i].push_back(aux);
            }
        }

        for(int i = 0; i < mat[0].size(); i++) {
            int val = M - mat[0][i];
            if(val >= 0)
                memMat[0][val] = true;
        }

        for(int i = 0; i < C-1; i++) {
            for(int j = 0; j < 201; j++) {
                if(memMat[i][j]) {
                    for(int k = 0; k < mat[i+1].size(); k++) {
                        int val = j - mat[i+1][k];
                        if(val >= 0)
                            memMat[i+1][val] = true;
                    }
                }
            }
        }

        int sol = -1;
        for(int i = 0; i < 201; i++) {
            if(memMat[C-1][i]){
                sol = i;
                break;
            }
        }

        //printMat();
        if(sol == -1) std::cout << "no solution" << '\n';
        else          std::cout << M-sol << '\n';
    }
    return 0;
}
