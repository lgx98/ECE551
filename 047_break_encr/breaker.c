#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t findMax(size_t * array, size_t len) {
  size_t maxIdx = 0;
  for (size_t i = 1; i < len; i++) {
    if (array[i] > array[maxIdx])
      maxIdx = i;
  }
  return maxIdx;
}

size_t breaker(FILE * f) {
  size_t letterCount[26] = {0};
  char c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      letterCount[c - 'a']++;
    }
  }
  size_t maxIdx = findMax(letterCount, 26);
  return maxIdx >= 4 ? maxIdx - 4 : maxIdx + 22;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  size_t key = breaker(f);
  printf("%ld\n", key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
