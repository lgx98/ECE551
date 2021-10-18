#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2)
    exit_error("Wrong Number of Arguments");
  FILE * f = open_file(argv[1], "r");
  catarray_t * cats = parseCat(f);
  printWords(cats);
  catarray_delete(cats);
  close_file(f);
  return EXIT_SUCCESS;
}
