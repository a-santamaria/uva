// 2 4 5 11 18 17
// -9 -15

#include <iostream>
#include <vector>
#include <algorithm>

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
    std::cin >> cases;
    while (cases--) {
        int f, x;
        cin>>f;
        std::vector<int> pos;
        std::vector<int> neg;
        for (int i = 0; i < f; i++) {
            cin>>x;
            if(x > 0) pos.push_back(x);
            else      neg.push_back(-x);
        }
        sort(pos.begin(), pos.end());
        sort(neg.begin(), neg.end());
        // print(pos);
        // print(neg);
        int indP = 0, indN = 0;
        int contF = 0;
        while (indP < pos.size() && indN < neg.size()) {
            bool entreP = false;
            while(indP < pos.size() && indN < neg.size()) {
                if(pos[indP] < neg[indN]) {
                    indP++;
                    entreP = true;
                } else if(pos[indP] == neg[indN]) {
                    while(indP < pos.size() && indN < neg.size() && neg[indN] == pos[indP]) {
                        indN++;
                        indP++;
                    }
                    if(indP > pos.size() || indN > neg.size()) break;
                    if(pos[indP] < neg[indN]) indN--;
                    else                      indP--;
                } else {
                    break;
                }
            }
            if(entreP) contF++;

            bool entreN = false;
            while(indP < pos.size() && indN < neg.size()) {
                if(neg[indN] < pos[indP]) {
                    indN++;
                    entreN = true;
                } else if(neg[indN] == pos[indP]) {
                    while(indP < pos.size() && indN < neg.size() && neg[indN] == pos[indP]) {
                        indN++;
                        indP++;
                    }
                    if(indP > pos.size() || indN > neg.size()) break;
                    if(pos[indP] < neg[indN]) indN--;
                    else                      indP--;
                } else {
                    break;
                }
            }
            if(entreN) contF++;
        }

        if(indP < pos.size() || indN < neg.size()) {
            contF++;
        }
        std::cout << contF << '\n';
    }
    return 0;
}
