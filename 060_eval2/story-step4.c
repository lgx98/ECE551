#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  char * file_cat = NULL;
  char * file_story = NULL;
  uint storyOpt = 0;
  if (argc == 3) {
    file_cat = argv[1];
    file_story = argv[2];
  }
  else if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      file_cat = argv[2];
      file_story = argv[3];
      storyOpt |= NO_REUSE;
    }
    else {
      exit_error("Unsupported Argument");
    }
  }
  else {
    exit_error("Wrong Number of Arguments");
  }

  FILE * f_cat = open_file(file_cat, "r");
  catarray_t * cats = parseCat(f_cat);
  close_file(f_cat);

  FILE * f_story = open_file(file_story, "r");
  tokenArr_t * story = parseStory(f_story);
  close_file(f_story);

  makeStory(story, cats, storyOpt);
  writeStory(stdout, story);
  tokenArr_delete(story);
  catarray_delete(cats);

  return EXIT_SUCCESS;
}
