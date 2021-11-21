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
  std::vector<std::pair<int, int> > path = s.getWinPath();
  for (std::vector<std::pair<int, int> >::iterator it = path.begin(); it != path.end();
       ++it) {
    if (it->second != 0) {
      std::cout << it->first << "(" << it->second << "),";
    }
    else {
      std::cout << it->first << "(win)" << std::endl;
    }
  }
  std::cout << argv[0] << std::endl;
  std::cout << argv[1] << std::endl;
  return EXIT_SUCCESS;
}
