#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2)
    exit_error("Wrong Number of Arguments");
  FILE * f = open_file(argv[1], "r");
  tokenArr_t * story = parseStory(f);
  makeStory(story, NULL, ALWAYS_CAT);
  writeStory(stdout, story);
  tokenArr_delete(story);
  close_file(f);
  return EXIT_SUCCESS;
}
