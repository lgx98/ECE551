#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

// print the error message to stderr, then exit with failure.
void error(const char * msg) {
  fprintf(stderr, "Error: %s, Exiting!\n", msg);
  exit(EXIT_FAILURE);
}

void printLines(char ** data, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    printf("%s", data[i]);
    free(data[i]);
  }
  free(data);
}

void parseLines(FILE * f) {
  char ** lines = NULL;
  char * curr = NULL;
  size_t sz;
  size_t i = 0;
  while (getline(&curr, &sz, f) >= 0) {
    lines = realloc(lines, (i + 1) * sizeof(*lines));
    lines[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(lines, i);
  printLines(lines, i);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    parseLines(stdin);
  }
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL)
        error("Failed to Open File");
      parseLines(f);
      if (fclose(f) != 0)
        error("Failed to Close File");
    }
  }
  return EXIT_SUCCESS;
}
