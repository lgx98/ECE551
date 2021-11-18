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
  s.play();
  return EXIT_SUCCESS;
}
