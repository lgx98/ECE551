#include <cstdlib>
#include <fstream>

#include "page.hpp"
#include "story.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Wrong Number of Arguments" << std::endl;
    exit(EXIT_FAILURE);
  }
  Story s(argv[1]);
  std::vector<int> depth = s.getDepth();
  for (int i = 0; i < (int)depth.size(); ++i) {
    if (depth[i] != -1) {
      std::cout << "Page " << i + 1 << ":" << depth[i] << std::endl;
    }
    else {
      std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
    }
  }
  return EXIT_SUCCESS;
}
