#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


bool cmp(string s1, string s2) {
    return (s1+s2 > s2+s1);
}

int main() {
    int n;

    while (cin>>n && n != 0) {
        std::vector<string> arr(n);
        int x;
        for (int i = 0; i < n; i++) {
            cin>>arr[i];
        }
        sort(arr.begin(), arr.end(), cmp);

        for (int i = 0; i < n; i++) {
            cout<<arr[i];
        }
        std::cout << '\n';
    }
    return 0;
}
