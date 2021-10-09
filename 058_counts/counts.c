
#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void one_count_free(one_count_t cnt) {
  free(cnt.key);
}

void counts_insert(counts_t * const cnts, const char * key) {
  //printf("-----%s-----\n", key);
  if (key == NULL) {
    //printf("Inserted <unknown>!\n");
    (cnts->count_unknown)++;
    return;
  }
  for (size_t i = 0; i < cnts->size; ++i) {
    if (strcmp(cnts->data[i].key, key) == 0) {
      //printf("Inserted %s!\n", cnts->data[i].key);
      (cnts->data[i].count)++;
      return;
    }
  }
  cnts->size++;
  //printf("New key %s\n", key);
  cnts->data = realloc(cnts->data, cnts->size * sizeof(*cnts->data));
  cnts->data[cnts->size - 1].count = 1;
  size_t len = strlen(key);
  cnts->data[cnts->size - 1].key =
      malloc((len + 1) * sizeof(*cnts->data[cnts->size - 1].key));
  strcpy(cnts->data[cnts->size - 1].key, key);
  cnts->data[cnts->size - 1].key[len] = '\0';
  //printf("Created %s!\n", cnts->data[cnts->size - 1].key);
  return;
}

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * cnt = malloc(sizeof(*cnt));
  cnt->data = NULL;
  cnt->size = 0;
  cnt->count_unknown = 0;
  return cnt;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  counts_insert(c, name);
  return;
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->size; i++) {
    fprintf(outFile, "%s: %zd\n", c->data[i].key, c->data[i].count);
  }
  if (c->count_unknown != 0) {
    fprintf(outFile, "<unknown> : %zd\n", c->count_unknown);
  }
  return;
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->size; i++) {
    one_count_free(c->data[i]);
  }
  free(c->data);
  free(c);
  return;
}
