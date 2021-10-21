#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void sortLines(std::istream & is) {
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(is, line))
    lines.push_back(line);
  if (!is) {
    std::cerr << "Error occurred when reading file\n";
    exit(EXIT_FAILURE);
  }
  std::sort(lines.begin(), lines.end());
  for (auto ln : lines)
    std::cout << ln << std::endl;
  return;
}

int main(int argc, char ** argv) {
  if (argc == 1)
    sortLines(std::cin);
  else
    for (ssize_t i = 1; i < argc; ++i) {
      std::ifstream ifs(argv[i], std::ifstream::in);
      if (!ifs.is_open()) {
        std::cerr << "Error opening file: " << argv[i] << std::endl;
        exit(EXIT_FAILURE);
      }
      sortLines(ifs);
      ifs.close();
    }
  return EXIT_SUCCESS;
}
