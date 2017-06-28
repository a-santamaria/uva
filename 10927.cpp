#include <iostream>
#include <cmath>
#include <algorithm>
#include <set>

using namespace std;

struct TPoint {
  double x, y, z;

  TPoint () {
    x = y = z = 0.0;
  }

  TPoint (double x, double y, double z) : x(x), y(y), z(z) {}

  double operator* (const TPoint& p) const {
    return x * p.x + y * p.y;
  }

  double operator% (const TPoint& p) const {
    return x * p.y - y * p.x;
  }

  double operator~ () const {
    return sqrt(x * x + y * y);
  }

  bool operator< (const TPoint& p) const {
    if(x == p.x) return y < p.y;
    else return x < p.x;
  }
};



bool cw(TPoint& p, TPoint& q) {
  if (p % q == 0.0 && p.x * q.x >= 0.0  && p.y * q.y >= 0.0) {
    return (~p) < (~q);
  }
  if(p.y == 0 && p.x > 0)
      return true; //angle of p is 0, thus q > p

  if(q.y == 0 && q.x > 0) 
      return false; //angle of q is 0 , thus p > q

  if(p.y > 0 && q.y < 0) 
      return true; //p is between 0 and 180, q between 180 and 360

  if(p.y < 0 && q.y > 0) 
        return false;
  if (p % q == 0.0) {
    return (~p) < (~q);
  }
  return (p % q) > 0.0;
}


int main() {
  int n;
  int casos = 1;
  TPoint points[100010];
  while(cin >> n && n != 0) {
    for (int i = 0; i < n; i++) {
      cin >> points[i].x >> points[i].y >> points[i].z;
    }

    sort(points, points+n, cw);

    TPoint prev = points[0];
    TPoint p;
    double h = points[0].z;
    set<TPoint> hidden;
    // cerr << " " << points[0].x << " " << points[0].y << " " << points[0].z << endl;
    for (int i = 1; i < n; i++) {
      // cerr << " " << points[i].x << " " << points[i].y << " " << points[i].z << endl;
      p = points[i];

      if(prev % p == 0.0) {
        if(h >= p.z) {
          // cerr << "lo tapa " << h << endl;
          hidden.insert(p);
        } else {
          h = p.z;
        }
      } else {
        h = p.z;
      }
      prev = p;
    }

    set<TPoint>::iterator it;
    cout << "Data set " << casos++ <<":\n";

    if(hidden.size() == 0)
      cout << "All the lights are visible.\n";
    else {
      cout << "Some lights are not visible:\n";
      bool first = true;
      for(it = hidden.begin(); it != hidden.end(); it++) {
        if(!first) cout << ";\n";
        first = false;
        cout << "x = " << it->x << ", y = " << it->y;
      }
      cout << ".\n";
    }
  }
  return 0;
}