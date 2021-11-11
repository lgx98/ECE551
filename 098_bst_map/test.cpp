#include <iostream>

#include "bstmap.h"
int main(void) {
  BstMap<int, int> map;
  map.add(60, 1);
  map.add(19, 2);
  map.add(93, 3);
  map.add(4, 4);
  map.add(25, 5);
  map.add(84, 6);
  map.add(1, 7);
  map.add(11, 8);
  map.add(21, 9);
  map.add(35, 10);
  map.add(70, 11);
  map.add(86, 12);
  std::cout << map;
  map.remove(70);
  std::cout << "RM 70\n";
  std::cout << map;
  map.remove(84);
  std::cout << "RM 84\n";
  std::cout << map;
  map.remove(93);
  std::cout << "RM 93\n";
  std::cout << map;
  map.remove(19);
  std::cout << "RM 19\n";
  std::cout << map;
  return 0;
}
