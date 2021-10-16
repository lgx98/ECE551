#include "circle.hpp"

#include <algorithm>
#include <cmath>
#include <cstdlib>

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = this->c.distanceFrom(otherCircle.c);
  double r1 = this->r;
  double r2 = otherCircle.r;

  // No intersection area.
  if (d >= (r1 + r2))
    return 0.0;

  // A circle contains the other.
  if (d <= std::abs(r1 - r2))
    return M_PI * std::min(r1, r2) * std::min(r1, r2);
  double ang1 = acos((r1 * r1 - r2 * r2 + d * d) / (2 * d * r1));
  double ang2 = acos((r2 * r2 - r1 * r1 + d * d) / (2 * d * r2));
  return ang1 * r1 * r1 + ang2 * r2 * r2 - d * r1 * sin(ang1);
}
