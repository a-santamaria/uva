#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>

using namespace std;

int main() {
  int n;
  while(std::cin >> n) {
      std::vector<int> v(n);
      for(int i = 0; i < n; i++){
          std::cin >> v[i];
      }
      int f, x, y;
      std::cin >> f;

      sort(v.begin(), v.end());
      int mindiff = 1e9;
      for(int i = 0; i < v.size(); i++) {
          int ff = f-v[i];
          if(ff > 0) {
              if( binary_search(v.begin()+i+1, v.end(), ff) ) {
                  if(abs(v[i] - ff) < mindiff) {
                      mindiff = abs(v[i] - ff);
                      x = v[i];
                      y = ff;
                  }
              }
          }
      }
      printf("Peter should buy books whose prices are %d and %d.\n\n", x, y);
  }
  return 0;
}
