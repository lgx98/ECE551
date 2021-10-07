#ifndef __KV_H__
#define __KV_H__

#include <stdlib.h>

struct _kvpair_t {
  //DEFINE ME!
  char * key;
  char * value;
};
typedef struct _kvpair_t kvpair_t;

void kvpair_free(const kvpair_t pair);

kvpair_t kvpair_parse_line(const char * line, const char delimeter);

struct _kvarray_t {
  //DEFINE ME!
  kvpair_t * data;
  size_t size;
};
typedef struct _kvarray_t kvarray_t;

void kvarray_free(kvarray_t arr);

void kvarray_push_back(kvarray_t * const arr, const kvpair_t pair);

kvarray_t * readKVs(const char * fname);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
