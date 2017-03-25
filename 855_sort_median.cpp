#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

void print(std::vector<int>& v) {
    std::cout << "---------------" << '\n';
    for(int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << '\n' << "---------------" << '\n';
}

int main() {
    int cases;
    cin>> cases;
    while(cases--) {
        int s, a, f, x, y;
        std::cin >> s >> a >> f;
        std::vector<int> fils;
        std::vector<int> cols;
        for(int i = 0; i < f; i++) {
            std::cin >> x  >> y;
            fils.push_back(x);
            cols.push_back(y);
        }
        sort(fils.begin(), fils.end());
        sort(cols.begin(), cols.end());
        // print(fils);
        // print(cols);
        int mid1 = (fils.size() / 2);
        if(fils.size() % 2 == 0) mid1--;
        int mid2 = (cols.size() / 2);
        if(cols.size() % 2 == 0) mid2--;
        printf("(Street: %d, Avenue: %d)\n", fils[mid1], cols[mid2]);
    }
}
