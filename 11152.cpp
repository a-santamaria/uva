#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int main() {
  cout.precision(4);
  cout << fixed;
  double arr[3];

  while(cin >> arr[0] >> arr[1] >> arr[2]) {
    sort(arr, arr+3);
    double R = arr[0] * arr[1] * arr[2] / sqrt( 
      (arr[0] + arr[1] + arr[2]) * 
      (arr[1] + arr[2] - arr[0]) *
      (arr[2] + arr[0] - arr[1]) * 
      (arr[0] + arr[1] - arr[2]));
    double C = M_PI * R * R;

    double p = (arr[0] + arr[1] + arr[2]) / 2.0;
    double T = sqrt(p*(p-arr[0]) * (p-arr[1]) * (p-arr[2]));

    double r = T * 2.0 / (arr[0] + arr[1] + arr[2]);
    double c = M_PI * r * r;
    cout << C - T << " " << T - c << " " << c << '\n';
  }
  return 0;
}