#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void error(const char * msg) {
  fprintf(stderr, "Error: %s, Exiting!\n", msg);
  exit(EXIT_FAILURE);
}

void kvpair_free(const kvpair_t pair) {
  free(pair.key);
  free(pair.value);
  return;
}

kvpair_t kvpair_parse_line(const char * line, const char delimeter) {
  const char * ptr_key = line;
  ptr_key = strchr(ptr_key, delimeter);
  if (ptr_key == NULL)
    error("No delimeter in line");

  const char * ptr_value = ptr_key;
  ptr_value = strchr(ptr_value, '\n');
  if (ptr_value == NULL)
    error("No '\n' in line");

  kvpair_t pair;

  size_t len_key = ptr_key - line;
  pair.key = malloc((len_key + 1) * sizeof(*pair.key));
  strncpy(pair.key, line, len_key);
  pair.key[len_key] = '\0';

  size_t len_value = ptr_value - ptr_key - 1;
  pair.value = malloc((len_value + 1) * sizeof(*pair.value));
  strncpy(pair.value, ptr_key + 1, len_value);
  pair.value[len_value] = '\0';

  return pair;
}

void kvarray_free(kvarray_t arr) {
  for (size_t i = 0; i < arr.size; ++i)
    kvpair_free(arr.data[i]);
  free(arr.data);
  return;
}

void kvarray_push_back(kvarray_t * const arr, const kvpair_t pair) {
  arr->data = realloc(arr->data, (arr->size + 1) * sizeof(*(arr->data)));
  arr->data[arr->size] = pair;
  (arr->size)++;
  return;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  // Open file
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("Could not open file");
    fprintf(stderr, "FileName: %s\n", fname);
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 0;

  kvarray_t * kvarr = malloc(sizeof(*kvarr));
  kvarr->data = NULL;
  kvarr->size = 0;
  while ((len = getline(&line, &sz, f)) >= 0)
    kvarray_push_back(kvarr, kvpair_parse_line(line, '='));
  free(line);

  // Close file
  if (fclose(f) != 0) {
    perror("Could not close file");
    fprintf(stderr, "FileName: %s\n", fname);
    exit(EXIT_FAILURE);
  }

  return kvarr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  kvarray_free(*pairs);
  free(pairs);
  return;
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; ++i)
    printf("key = '%s' value = '%s'\n", pairs->data[i].key, pairs->data[i].value);
  return;
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->size; ++i)
    if (strcmp(pairs->data[i].key, key) == 0)
      return pairs->data[i].value;
  return NULL;
}
