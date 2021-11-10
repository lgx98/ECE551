#include <iostream>

#include "bstmap.h"
int main(void) {
  BstMap<int, int> a;
  std::cout << a << std::endl;
  a.add(45, 0);
  std::cout << a << std::endl;
  a.add(34, 1);
  std::cout << a << std::endl;
  a.add(24, 2);
  std::cout << a << std::endl;
  a.add(56, 3);
  std::cout << a << std::endl;
  a.add(12, 4);
  std::cout << a << std::endl;
  return 0;
}
