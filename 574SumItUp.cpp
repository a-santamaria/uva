#include <iostream>
#include <cstring>
#include <set>
#include <sstream>
using namespace std;

bool marcas[15];
int nums[15];
int n;
int t;
set<string> ans;


void printState() {
    stringstream ss;
    bool first = true;
    for(int i = 0 ; i < n; i++) {
        if(marcas[i]){
            if(first) {
                ss << nums[i];
                first = false;
            }
            else ss << "+" << nums[i];
        }
    }
    string s;
    ss >> s;
    if (ans.find(s) == ans.end()) {
        std::cout << s << '\n';
        ans.insert(s);
    }
}
bool atleastOnes;
void bt(int voy, int sum) {
    // std::cout << "sum " << sum << '\n';
    if(sum == t) {
        printState();
        atleastOnes = true;
        return;
    }
    if(sum > t || voy == n) return;
    marcas[voy] = true;
    bt(voy+1, sum+nums[voy]);
    marcas[voy] = false;
    bt(voy+1, sum);
}

int main() {
    int caso = 0;
    while(cin>>t>>n && t != 0 && n != 0) {
        memset(marcas, false, sizeof(marcas));
        ans.clear();
        atleastOnes = false;
        for(int i = 0; i < n; i++) {
            std::cin >> nums[i];
        }
        std::cout << "Sums of " << t << ":" << '\n';
        bt(0, 0);
        if(!atleastOnes) std::cout << "NONE" << '\n';
    }
    return 0;
}
