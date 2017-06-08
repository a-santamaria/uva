#include <iostream>
#include <cstring>

using namespace std;

bool marcas[20];
int state[20];
int n;

int prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

bool isPrime(int n) {
    for(int i = 0 ; i < 13; i++)
        if(n == prime[i]) return true;
    return false;
}

void printState() {
    for(int i = 0 ; i < n-1; i++) {
        std::cout << state[i] <<  " ";
    }
    std::cout << state[n-1] << '\n';
}

void bt(int voy) {
    if(voy == n) {
        if(isPrime(state[voy-1] + 1))
            printState();
        return;
    }
    for(int i = 2; i <= n; i++) {
        if(!marcas[i]) {
            if(isPrime(state[voy-1] + i)) {
                state[voy] = i;
                marcas[i] = true;
                bt(voy+1);
                marcas[i] = false;
            }
        }
    }
}

int main() {
    int caso = 0;
    while(cin>>n) {
        memset(marcas, false, sizeof(marcas));
        state[0] = 1;
        if(caso != 0) std::cout << '\n';
        std::cout << "Case " << ++caso << ":" << '\n';
        bt(1);
    }
    return 0;
}
