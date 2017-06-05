#include <iostream>

using namespace std;

int main() {
    int n;
    while(cin>>n && n != 0) {
        int arr[n];
        for(int i = 0; i < n; i++) {
            cin>>arr[i];
        }

        int sol = -1;
        int sum = -1;
        for(int i = 0; i < n; i++) {
            sum += arr[i];
            if(sum < 0) sum = 0;
            sol = max(sum, sol);
        }
        if(sol > 0)
            std::cout << "The maximum winning streak is " << sol << ".\n";
        else
            std::cout << "Losing streak." << '\n';
    }
    return 0;
}
