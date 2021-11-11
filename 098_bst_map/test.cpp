#include <iostream>

#include "bstmap.h"
int main(void) {
  BstMap<int, int> a;
  //std::cout << a << std::endl;
  a.add(45, 0);
  //std::cout << a << std::endl;
  a.add(34, 1);
  //std::cout << a << std::endl;
  a.add(24, 2);
  //std::cout << a << std::endl;
  a.add(56, 3);
  //std::cout << a << std::endl;
  a.add(25, 4);
  std::cout << a << std::endl;
  BstMap<int, int> b(a);
  std::cout << b << std::endl;
  //std::cout << b << std::endl;
  //std::cout << a.lookup(56) << std::endl;
  // std::cout << a.lookup(52) << std::endl;
  //std::cout << a << std::endl;
  a.remove(45);
  std::cout << a << std::endl;
  a = b;
  std::cout << a << std::endl;
  return 0;
}
