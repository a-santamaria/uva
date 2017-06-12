#include <iostream>
#include <cmath>
#include <vector>
#include <limits>


using namespace std;

struct Vec {
  double x, y;

  Vec(double x, double y): x(x), y(y) {}
  double norm_sq() {
    return x * x + y * y;
  }
  Vec scale(double s) {
    return Vec(x*s, y*s);
  }

  void toString() {
    cout << "(" << x << ", " << y << ")" << endl;
  }
};

struct Point {
  double x, y;

  Point() {}
  Point(double x, double y) : x(x), y(y) {}
  Point translate(Vec v) {
    return Point(x + v.x, y + v.y);
  }

  bool operator== (const Point &other) const {
    return (x == other.x && y == other.y);
  }

  void toString() {
    cout << "(" << x << ", " << y << ")" << endl;
  }
};

Vec toVec(Point p, Point q) {
  return Vec(q.x - p.x, q.y - p.y);
}

double dot(Vec p, Vec q) {
  return p.x * q.x + p.y * q.y;
}

double dist(Point p, Point q) {
  return sqrt((p.x - q.x)*(p.x - q.x) + (p.y - q.y)*(p.y - q.y));
}



int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  
  cout.precision(4);
  cout << fixed;

  int n;
  Point m;
  
  while(cin >> m.x >> m.y >> n) {
    vector<Point> points(n+1);
    for(int i = 0; i < n+1; i++) {
      cin >> points[i].x >> points[i].y;
    }

    double minDist = std::numeric_limits<double>::max();
    double d;
    Point currMin(0,0);
    for(int i = 0; i < n; i++) {
      d = dist(m, points[i]);
      if(d < minDist) {
        minDist = d;
        currMin = points[i];
      }
      if(points[i] == points[i+1]) continue;
      d = dist(m, points[i+1]);
      if(d < minDist) {
        minDist = d;
        currMin = points[i+1];
      }
      
      Vec ab = toVec(points[i], points[i+1]);
      Vec am = toVec(points[i], m);
      double u = dot(ab, am) / ab.norm_sq();
      if (u <= 0 || u > 1) {
        continue;
      }
      Point p  = points[i].translate(ab.scale(u));
      d = dist(p, m);
      if(d < minDist) {
        minDist = d;
        currMin = p;
      }
    }
    cout << currMin.x << '\n' << currMin.y << '\n';
  }
  return 0;
}