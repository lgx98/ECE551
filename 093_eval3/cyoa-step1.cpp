#include <cstdlib>
#include <fstream>

#include "./page.hpp"
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Wrong Number of Arguments" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::ifstream f(argv[1], std::ifstream::in);
  if (!f) {
    std::cerr << "Error Opening File: " << argv[1] << std::endl;
  }
  Page * p = parsePage(f);
  std::cout << *p;
  delete p;
  f.close();
  return EXIT_SUCCESS;
}