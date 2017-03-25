// 2 4 5 11 18 17
// -9 -15

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Num {
    int num;
    bool sign;
    Num(int n) {
        if(n > 0) {
            num = n;
            sign = true;
        } else {
            num = -n;
            sign = false;
        }
    }
    bool operator< (const Num& other) const {
        return num < other.num;
    }
};

void print(std::vector<Num>& v) {
    std::cout << "---------------" << '\n';
    for(int i = 0; i < v.size(); i++) {
        std::cout << v[i].num << " ";
    }
    std::cout << '\n' << "---------------" << '\n';
}
int main() {
    int cases;
    std::cin >> cases;
    while (cases--) {
        int f, x;
        cin>>f;
        std::vector<Num> vec;
        for (int i = 0; i < f; i++) {
            cin>>x;
            vec.push_back(Num(x));
        }
        sort(vec.begin(), vec.end());
        // print(vec);
        int contF = 0;
        bool currSign = vec[0].sign;
        for(int i = 1; i < vec.size(); i++) {
            if(currSign != vec[i].sign) {
                currSign = vec[i].sign;
                contF++;
            }
        }
        if(contF != 0) contF++;
        std::cout << contF << '\n';
    }
    return 0;
}
