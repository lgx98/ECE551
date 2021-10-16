#include "point.hpp"

class Circle {
 private:
  Point c;
  const double r;

 public:
  Circle(Point c, double r) : c(c), r(r){};
  void move(double dx, double dy) { c.move(dx, dy); };
  double intersectionArea(const Circle & otherCircle);
};
