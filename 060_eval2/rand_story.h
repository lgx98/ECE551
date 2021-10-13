#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>

#include "provided.h"

//any functions you want your main to use

typedef enum _tokenType_t { STRING, BLANK } tokenType_t;

typedef struct _token_t {
  tokenType_t type;
  char * str;
} token_t;

token_t * token_new(const tokenType_t type, const char * str);

void token_delete(token_t token);

typedef struct _tokenArr_t {
  token_t * tokens;
  size_t n_tokens;
  size_t n_avail;
} tokenArr_t;

tokenArr_t * tokenArr_new(void);

void tokenArr_delete(tokenArr_t * arr);

void tokenArr_push_back(tokenArr_t * arr, tokenArr_t token);

tokenArr_t * parseStory(FILE * f);

catarray_t * parseCat(FILE * f);

#endif
