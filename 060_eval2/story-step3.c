#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3)
    exit_error("Wrong Number of Arguments");

  FILE * f_cat = open_file(argv[1], "r");
  catarray_t * cats = parseCat(f_cat);
  close_file(f_cat);

  FILE * f_story = open_file(argv[2], "r");
  tokenArr_t * story = parseStory(f_story);
  close_file(f_story);

  makeStory(story, cats, 0);
  writeStory(stdout, story);
  tokenArr_delete(story);
  catarray_delete(cats);

  return EXIT_SUCCESS;
}
