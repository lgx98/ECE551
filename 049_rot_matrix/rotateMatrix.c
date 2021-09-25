#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLS 10
#define ROWS 10

void error(const char * msg) {
  fprintf(stderr, "Error: %s, Exiting!\n", msg);
  exit(EXIT_FAILURE);
}

void readMatrix(char matrix[ROWS][COLS], FILE * f) {
  int c;
  for (size_t i = 0; i < ROWS; ++i) {
    for (size_t j = 0; j < COLS; ++j) {
      c = fgetc(f);
      if (c == EOF)
        error("Input File Too Short");
      if (c == '\n')
        error("Line Too Short");
      matrix[i][j] = c;
    }
    c = fgetc(f);
    if (c == EOF)
      error("Input File Too Short");
    if (c != '\n')
      error("Line Too Long");
  }
  c = fgetc(f);
  if (c != EOF)
    error("Input File Too Long");
  return;
}

void printRotated(char matrix[ROWS][COLS]) {
  for (size_t i = 0; i < ROWS; ++i) {
    for (size_t j = 0; j < COLS; ++j) {
      putchar(matrix[COLS - 1 - j][i]);
    }
    putchar('\n');
  }
  return;
}

int main(int argc, char * argv[]) {
  if (argc != 2)
    error("Wrong Number of Arguments");

  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }

  char matrix[ROWS][COLS];
  readMatrix(matrix, f);
  printRotated(matrix);

  if (fclose(f) != 0) {
    perror("Could not close file");
    exit(EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}
