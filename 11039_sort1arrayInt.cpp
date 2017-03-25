// 2 4 5 11 18 17
// -9 -15

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool comparator(int a, int b) {
    return abs(a) < abs(b);
}

void print(std::vector<int>& v) {
    std::cout << "---------------" << '\n';
    for(int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << '\n' << "---------------" << '\n';
}
int main() {
    int cases;
    std::cin >> cases;
    while (cases--) {
        int f, x;
        cin>>f;
        std::vector<int> vec;
        for (int i = 0; i < f; i++) {
            cin>>x;
            vec.push_back(x);
        }
        sort(vec.begin(), vec.end(), comparator);
        // print(vec);
        int contF = 0;
        for(int i = 1; i < vec.size(); i++) {
            if( (vec[i-1] < 0 && vec[i] > 0) || (vec[i-1] > 0 && vec[i] < 0) ) {
                contF++;
            }
        }
        if(contF != 0) contF++;
        std::cout << contF << '\n';
    }
    return 0;
}
